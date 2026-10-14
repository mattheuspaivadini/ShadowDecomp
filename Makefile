# Shadow of the Colossus (USA) matching decompilation - build driver.
#
# Everything that needs a Linux toolchain runs inside WSL2; `make` itself can be
# run from Windows (the recipes shell out to `wsl`) or from inside WSL.
# See docs/toolchain.md and docs/compiler_flags.mk.

WSL   ?= wsl -d Ubuntu -u root --
REPO  := $(CURDIR)

.PHONY: all build check targets diff report objdiff clean help verify matrix container elf-diff

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
	@echo "make report         matched functions / matched bytes"
