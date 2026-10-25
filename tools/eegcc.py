#!/usr/bin/env python3
"""Shared ee-gcc2.96 helpers for the build (flags, source staging, C compile).

Runs inside WSL2 (see docs/toolchain.md). Two host quirks are handled here:

* the ee-gcc2.96 driver is a 32-bit i386 binary whose `cc1`/`as` are found on
  `PATH`, so `tools/cc/eegcc.sh` must be used instead of `bin/ee-gcc` directly;
* `cc1` cannot `stat` files on `/mnt/c` (drvfs) - it dies with
  "Value too large for defined data type" - so `src/` and `include/` are
  mirrored into a native ext4 work tree before compiling.
"""
from __future__ import annotations

import filecmp
import os
import re
import shutil
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
EEGCC = ROOT / "tools" / "cc" / "eegcc.sh"
CC_DIR = ROOT / "tools" / "cc"
FLAGS_MK = ROOT / "config" / "compiler_flags.mk"
WORK = Path(os.environ.get("SOT_WORK", str(Path.home() / "shadowdecomp-work")))

# symbols that must never be stripped from an object before linking
_NO_STRIP = (".text", ".data", ".rodata", ".sdata", ".sbss", ".bss", ".lit4")


def _read_mk() -> dict[str, str]:
    out: dict[str, str] = {}
    if not FLAGS_MK.exists():
        return out
    text = FLAGS_MK.read_text(encoding="utf-8")
    # join continuation lines
    text = re.sub(r"\\\n", " ", text)
    for line in text.splitlines():
        line = line.split("#", 1)[0].strip()
        m = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)\s*:?=\s*(.*)$", line)
        if m:
            out[m.group(1)] = m.group(2).strip()
    # expand $(VAR) references (the .mk uses make variables to compose flags)
    ref = re.compile(r"\$\(([A-Za-z_][A-Za-z0-9_]*)\)|\$\{([A-Za-z_][A-Za-z0-9_]*)\}")
    for _ in range(8):
        changed = False
        for k, v in list(out.items()):
            nv = ref.sub(lambda m: out[m.group(1) or m.group(2)], v) if "$(" in v or "${" in v else v
            if nv != v:
                out[k] = nv
                changed = True
        if not changed:
            break
    return out


_MK = _read_mk()


def flag(name: str, default: str = "") -> str:
    return _MK.get(name, default)


def cflags() -> list[str]:
    """The pinned C flags, as a list."""
    raw = flag("EE_CFLAGS", "-O2 -g2 -G8 -Iinclude")
    return raw.split()


def cflags_for(extra: list[str] | None = None) -> list[str]:
    """The pinned C flags, plus per-function extras.

    NOTE (ee-gcc2.96 quirk, measured): the `-g` level is sticky - once any
    `-g`/`-g2` is seen a later `-g0` has no effect. So an explicit `-g...` in
    `extra` must *replace* the pinned `-g2`, not be appended after it.

    An explicit `-O...` in `extra` likewise *replaces* the pinned `-O2` (used by
    `tools/opt_sweep.py` to discriminate the optimisation level; the manifest
    itself never carries an `-O`). This keeps the applied flag set unambiguous.
    """
    extra = extra or []
    base = cflags()
    if any(re.match(r"^-g", f) for f in extra):
        base = [f for f in base if not re.match(r"^-g", f)]
    if any(re.match(r"^-O", f) for f in extra):
        base = [f for f in base if not re.match(r"^-O", f)]
    return base + extra


def default_compiler() -> str:
    """Distribution used when a translation unit does not pin one."""
    return flag("EE_C_COMPILER", "ee-gcc2.96")


def resolve_compiler(token: str | None) -> str:
    """Map a manifest compiler token to an `EE_GCC_DIR` selector.

    Tokens: None/'' -> EE_C_COMPILER; `29`/`2.9` -> EE_C_COMPILER_29;
    `96`/`2.96` -> EE_C_COMPILER; anything else is taken verbatim (a name under
    tools/cc/ or a path), so a new distribution needs no tool change.

    A `wine:<name>` selector marks a Windows (PE) distribution that must be run
    through wine (see `compile_c`).
    """
    if not token:
        return default_compiler()
    return {
        "96": flag("EE_C_COMPILER", "ee-gcc2.96"),
        "2.96": flag("EE_C_COMPILER", "ee-gcc2.96"),
        "296": flag("EE_C_COMPILER", "ee-gcc2.96"),
        "29": flag("EE_C_COMPILER_29", "ee-gcc2.9-991111-01"),
        "2.9": flag("EE_C_COMPILER_29", "ee-gcc2.9-991111-01"),
    }.get(token, token)


WINE_PREFIX = os.environ.get("SOT_WINEPREFIX", str(Path.home() / ".wine-sotc"))


def is_wine(sel: str) -> bool:
    return sel.startswith("wine:")


def wine_dist_dir(sel: str) -> Path:
    """tools/cc directory of a `wine:<name>` selector (name or path)."""
    name = sel[len("wine:"):]
    p = Path(name)
    return p if p.is_absolute() else CC_DIR / name


def stage_sources(verbose: bool = False) -> None:
    """Mirror src/ + include/ (+ overlay sources) into the native work tree."""
    for name in ("src", "include", "overlays"):
        src_root = ROOT / name
        if not src_root.exists():
            continue
        for p in src_root.rglob("*"):
            dst = WORK / name / p.relative_to(src_root)
            if p.is_dir():
                dst.mkdir(parents=True, exist_ok=True)
            elif not dst.exists() or not filecmp.cmp(p, dst, shallow=False):
                dst.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(p, dst)
                if verbose:
                    print(f"  staged {p.relative_to(ROOT)}")


def compile_c(src_rel: str, out_obj: Path, extra: list[str] | None = None,
              compiler: str | None = None, *, stage: bool = True) -> str:
    """Compile `src_rel` (repo-relative, e.g. src/cod/002FE0.c) to `out_obj`.

    Returns an error string ('' on success). `out_obj` may live on /mnt/c.

    `compiler` selects an EE-GCC distribution (a name under tools/cc/, a path,
    or a token resolved by `resolve_compiler`); None uses the pinned default
    (EE_C_COMPILER). The selector is passed to `tools/cc/eegcc.sh` through the
    EE_GCC_DIR environment variable.

    `stage=False` skips the (per-call) source mirror for callers that stage
    once up front.
    """
    if stage:
        stage_sources()
    staged = WORK / src_rel
    if not staged.exists():
        return f"staged source missing: {staged}"
    out_obj.parent.mkdir(parents=True, exist_ok=True)
    sel = resolve_compiler(compiler)
    env = dict(os.environ)
    if is_wine(sel):
        dist = wine_dist_dir(sel)
        drv = dist / "bin" / "ee-gcc.exe"
        if not drv.exists():
            return f"no wine driver: {drv}"
        cmd = ["wine", str(drv), "-c", *cflags_for(extra),
               str(staged), "-o", str(out_obj)]
        env.setdefault("WINEDEBUG", "-all")
        env.setdefault("WINEPREFIX", WINE_PREFIX)
    else:
        cmd = [str(EEGCC), "-c", *cflags_for(extra),
               str(staged), "-o", str(out_obj)]
        env["EE_GCC_DIR"] = sel
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=str(WORK), env=env)
    if r.returncode != 0 or not out_obj.exists():
        lines = (r.stderr or r.stdout).strip().splitlines()
        return " | ".join(lines[:4]) if lines else "ee-gcc failed"
    return ""


def section_sizes(obj: Path) -> dict[str, int]:
    """Names -> sizes of the allocatable sections of an ELF32 object."""
    import struct

    data = obj.read_bytes()
    e_shoff, = struct.unpack_from("<I", data, 0x20)
    e_shentsize, e_shnum, e_shstrndx = struct.unpack_from("<HHH", data, 0x2E)
    shs = [struct.unpack_from("<10I", data, e_shoff + i * e_shentsize)
           for i in range(e_shnum)]
    shstr = data[shs[e_shstrndx][4]:shs[e_shstrndx][4] + shs[e_shstrndx][5]]

    def nm(off: int) -> str:
        end = shstr.find(b"\0", off)
        return shstr[off:end].decode("utf-8", "replace")

    out: dict[str, int] = {}
    for sh in shs:
        name = nm(sh[0])
        if sh[2] & 0x2 and sh[5]:  # sh[2] = sh_flags; SHF_ALLOC, non-empty
            out[name] = sh[5]
    return out
