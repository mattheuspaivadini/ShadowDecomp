# =============================================================================
# config/compiler_flags.mk - single source of truth for the build flags
# (Phase 3, pinned 2026-10-14 by experiment; see docs/compiler.md)
# =============================================================================
#
# Consumed by tools/build.py (mixed C/asm build) and readable by make/ninja.
# Only `-O2 -g2 -G8` is evidenced; everything else is left at the toolchain
# default on purpose (an unevidenced flag cannot be assumed).

# --- C compiler ---------------------------------------------------------------
# ee-gcc from decompme/compilers (tools/cc/, gitignored), unpacked one dir per
# published build. tools/cc/eegcc.sh is a thin wrapper that selects the
# distribution with $EE_GCC_DIR; the driver is a 32-bit i386 binary, finds
# cc1/as through PATH, and cannot stat sources on /mnt/c (drvfs).
EE_GCC      ?= tools/cc/eegcc.sh

# Default distribution for translation units that do not pin their own.
EE_C_COMPILER      := ee-gcc2.96
# Alternate revision. Evidence (docs/compiler.md section 4.3): nine functions
# are only reproduced by the 2.9-991111 generation (e.g. `lui/ori 0xFFFFFFFE`
# for -2, split `lui/addiu`+`%lo` addressing, the R5900 `mult` constant stride).
# These three assets are codegen-identical on every case tested:
#   ee-gcc2.9-991111-01, ee-gcc2.9-991111-xz, ee-gcc2.9-991111a
EE_C_COMPILER_29   := ee-gcc2.9-991111-01

# Pin 2026-10-14, 11/11 Phase-3 cases byte-exact:
#   -O2   optimisation level (SOTC's default).  Discriminated from -O1 and -Os
#         by the 92-function sweep (tools/opt_sweep.py): 39 functions fail at
#         -O1 and 14 at -Os, while -O2 and -O3 are codegen-identical on the
#         whole corpus (-O3 = -O2 + -finline-functions, and no TU here has an
#         inlinable helper).  See docs/compiler.md section 2.2.
#   -g2   debug level. NOT cosmetic: -g/-g2 disable the delayed-branch
#         scheduler, which is required to reproduce the original's
#         "compute, then jr, then nop" epilogues.
#   -G8   small-data limit (ee-gcc default). Objects <= 8 bytes are addressed
#         %gp_rel, larger ones absolute lui/%lo - exactly what the image shows.
EE_C_OPT      := -O2
EE_C_DEBUG    := -g2
EE_C_SMALLDATA := -G8
EE_C_WARN     :=
EE_C_INCLUDES := -Iinclude
EE_CFLAGS     := $(EE_C_OPT) $(EE_C_DEBUG) $(EE_C_SMALLDATA) $(EE_C_INCLUDES) $(EE_C_WARN)

# --- Assembler / linker (Debian binutils, NOT Sony ee-as/ee-ld) ---------------
EE_AS         := mips-linux-gnu-as
EE_ASFLAGS    := -EL -march=5900 -mabi=eabi -no-pad-sections -Iinclude -I.
EE_OBJCOPY    := mips-linux-gnu-objcopy
# GAS marks .text/.data 16-byte aligned; the original is 4-byte aligned.
EE_OBJCOPY_ALIGN := --set-section-alignment .text=4 --set-section-alignment .data=4 \
                    --set-section-alignment .rodata=4 --set-section-alignment .lit4=4 \
                    --set-section-alignment .sdata=4 --set-section-alignment .sbss=4 \
                    --set-section-alignment .bss=4
EE_LD         := mips-linux-gnu-ld
EE_LDFLAGS    := -EL

# --- Acceptance gate ----------------------------------------------------------
# The flat load image must stay byte-identical while C replaces .s one
# function at a time.
ROM_SHA1      := 6f853f644a4279db18c15ceb8ee1d2a8b87a7b39
ROM_SIZE      := 237952
