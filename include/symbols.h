#ifndef SYMBOLS_H
#define SYMBOLS_H

/* Declarations for symbols that are still auto-named by splat
 * (`D_<vaddr>` / `func_<vaddr>`). One declaration per entry is added as the
 * corresponding function is decompiled; the type is evidence-backed.
 * Addresses live in config/symbol_addrs.txt.
 *
 * *** Addressing mode rule (Phase 3, evidence) ***
 * ee-gcc2.96 emits `%gp_rel` for objects it believes are small data (`-G8`,
 * the default) and `lui/%hi + %lo` for everything else. In the original image:
 *
 *   .sdata / .sbss  (inside [_gp-0x8000, _gp+0x7FFF])  -> 100 % `%gp_rel`
 *   .data / .bss    (outside that window)             -> 100 % absolute
 *
 * Debian `mips-linux-gnu-ld` refuses to relax an out-of-range `%gp_rel`
 * ("relocation truncated to fit"), so an object that the original addresses
 * absolutely must be declared so that ee-gcc itself picks absolute addressing:
 * use `__attribute__((section(".data")))` (verified: tools/cc/probe_section.sh)
 * or a declared size > 8 bytes. `D_ABS` below documents the intent.
 */

/* ---- .sdata / .sbss : gp-relative (place them anywhere in [_gp-0x8000, _gp+0x7FFF]) *
 * offsets are relative to _gp = 0x00141D70. */
#define D_SMALL extern
D_SMALL int D_00139E04;   /* .sdata, _gp-0x7F6C  func_00101A48/_00101A30 */
D_SMALL int D_0013A11C;   /* .sbss,  _gp-0x3C54  func_00104F58 */
D_SMALL int D_0013A16C;   /* .sbss,  _gp-0x3C04  func_00106380 */
D_SMALL int D_0013A170;   /* .sbss,  _gp-0x3C00  func_00106380 */

/* ---- .data / .rodata / .bss : absolute addressing (declared non-small) */
#define D_ABS extern __attribute__((section(".data")))
D_ABS int D_001329A4;         /* .data   0x001329A4  func_0010FBE8 */
D_ABS int D_00133920;         /* .data   0x00133920  func_00110640 */
D_ABS int D_00133940;         /* .data   0x00133940  func_00111D50 */
D_ABS int D_00133970;         /* .data   0x00133970  func_00113520 */
D_ABS int D_00135C60;         /* .data   0x00135C60  func_00127528 */
D_ABS int D_00135958;         /* .data   0x00135958  func_00122448 */

/* .bss / .rodata objects of unknown size: unknown size is already non-small. */
extern char D_0013BF90[];     /* .bss    0x0013BF90  func_001029C8 */
extern char D_0013C790[];     /* .bss    0x0013C790  func_00102C58 */
extern char D_0013CF90[];     /* .bss    0x0013CF90  func_00103CA8 */
extern char D_00139B08[];     /* .rodata 0x00139B08  func_0012E520 */
extern char D_0014B358[];     /* .bss    0x0014B358  func_00112908/_00112BD0/_00112BE8 */
extern int  D_0014B500[];     /* .bss    0x0014B500  func_001128D0/_001128E8 */
extern int  D_001339B0[];     /* .data   0x001339B0  func_00114918 */
extern char D_0013D840[];     /* .bss    0x0013D840  func_00104E78 */

/* ---- Session 4: 256-entry int tables (uniform -> absolute addressing) */
extern int  D_0013B790[256];  /* .bss    0x0013B790  func_001028F0/_00102A40 (_002500.._002BD8) */
extern int  D_0013BB90[256];  /* .bss    0x0013BB90  func_00102930/_00102A00 (_002500.._002BD8) */

/* ---- hardware registers (uncached EE addresses) */
#define HWREG(addr) (*(volatile unsigned int *)(addr))

/* ---- Session 4, step 2: newly confirmed data objects --------------------- */
/* .data doubly-linked list head used by func_00110998 (next at 0x0, prev at
 * 0x4). Declared as an array so the access is absolute, not %gp_rel. */
extern void *D_00133930[];

#endif /* SYMBOLS_H */
