# =============================================================================
# config/compiler_flags.mk - single source of truth for the build flags
# (Phase 3, pinned 2026-10-14 by experiment; see docs/compiler.md)
# =============================================================================
#
# Consumed by tools/build.py (mixed C/asm build) and readable by make/ninja.
# Only `-O2 -g2 -G8` is evidenced; everything else is left at the toolchain
# default on purpose (an unevidenced flag cannot be assumed).

# --- C compiler ---------------------------------------------------------------
# ee-gcc2.96 from decompme/compilers (tools/cc/, gitignored).
# tools/cc/eegcc.sh is a thin wrapper: the driver is a 32-bit i386 binary and
# finds cc1/as through PATH, and it cannot stat sources on /mnt/c (drvfs).
EE_GCC      ?= tools/cc/eegcc.sh

# Pin 2026-10-14, 11/11 Phase-3 cases byte-exact:
#   -O2   optimisation level (SOTC's default; not yet discriminated from
#         -O1/-O3/-Os by small functions -> revisit with larger units)
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
