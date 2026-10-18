# Shadow of the Colossus (USA) matching decompilation - build driver.
#
# Everything that needs a Linux toolchain runs inside WSL2; `make` itself can be
# run from Windows (the recipes shell out to `wsl`) or from inside WSL.
# See docs/toolchain.md and docs/compiler_flags.mk.

# From Windows the recipes launch WSL, and `$(CURDIR)` is a Windows path
# (`C:/...`) that `cd` inside WSL cannot use — translate it with `wslpath`.
# From inside WSL the launcher is empty and `$(CURDIR)` is already a Linux path.
ifeq ($(OS),Windows_NT)
WSL   ?= wsl -d Ubuntu -u root --
REPO  := $(shell wsl -d Ubuntu -u root -- wslpath $(CURDIR))
else
WSL   ?=
REPO  := $(CURDIR)
endif

.PHONY: all build check targets diff report objdiff clean help verify matrix container elf-diff score fast

all: check

## Build the image and require the byte-exact hash (the gate for every change).
check build:
	$(WSL) bash -lc "cd $(REPO) && python3 tools/build.py --jobs 8"

## Verify every function in config/c_sources.txt byte-exact (per instruction).
verify:
	$(WSL) bash -lc "cd $(REPO) && python3 tools/verify_c.py"

## Rebuild the compiler x function match matrix (WINE=1 to include the PE builds).
matrix:
	$(WSL) bash -lc "cd $(REPO) && python3 tools/cc_matrix.py --set all $(if $(WINE),--wine,)"

## Reshape the ld output into the original ELF container (step 6); --check fails
## if it is not byte-identical to the original.
container:
	$(WSL) bash -lc "cd $(REPO) && python3 tools/containerize.py --check"

## Compare the ELF container: our build/SCUS_974.72.elf vs extracted/SCUS_974.72.
elf-diff:
	$(WSL) bash -lc "cd $(REPO) && python3 tools/elf_container_diff.py"

## Build + also emit the objdiff target objects.
targets:
	$(WSL) bash -lc "cd $(REPO) && python3 tools/build.py --targets --jobs 8"

## Regenerate objdiff.json (unit list) and the target objects.
objdiff: targets
	python tools/gen_objdiff.py

## Diff one function:  make diff F=func_001128C0
diff:
	python tools/diff_func.py $(F)

## Score drafts inside WSL (the scorers call the Linux EE-GCC, so they fail
## from Windows Python):  make score STEMS=0053F0,001AA0 [DRAFTS=build/s28/drafts]
DRAFTS ?= build/s28/drafts
score:
	$(WSL) bash -lc "cd $(REPO) && python3 tools/score_drafts.py --stems $(STEMS) --drafts-dir $(DRAFTS) --only-draft --jobs 4"

## Fast per-function byte-exact check inside WSL:  make fast [STEMS="0053F0 001AA0"]
fast:
	$(WSL) bash -lc "cd $(REPO) && python3 build/s10/verify_fast.py $(STEMS) --jobs 4"

## Progress summary.
report:
	python tools/report.py

clean:
	$(WSL) bash -lc "cd $(REPO) && rm -rf build/asm build/tmp build/target build/phase3"

help:
	@echo "make check          build + require the pinned SHA-1 (default)"
	@echo "make verify         verify_c.py: every listed function byte-exact"
	@echo "make matrix         compiler x function match matrix (WINE=1: + PE)"
	@echo "make container      reshape build/SCUS_974.72.elf into the original container"
	@echo "make elf-diff       compare the ELF container vs the original"
	@echo "make targets        also assemble objdiff target objects"
	@echo "make objdiff        regenerate objdiff.json"
	@echo "make diff F=<func>  build and diff one function"
	@echo "make score STEMS=a,b  score drafts in \$$DRAFTS (WSL)"
	@echo "make fast [STEMS=..]  verify_fast.py (WSL)"
	@echo "make report         matched functions / matched bytes"
