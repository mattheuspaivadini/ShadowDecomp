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
 * or a declared size > 8 bytes.
 */

/* .sdata (gp-relative) */
extern int D_00139E04;   /* evidence: %gp_rel(D_00139E04) in func_00101A48/_00101A30 */

/* .data (outside the gp window -> absolute lui/%lo addressing) */
extern int D_00133940 __attribute__((section(".data")));
extern int D_001339B0[] __attribute__((section(".data")));
extern char D_0014B358[];    /* .bss: unknown size is already non-small */

#endif /* SYMBOLS_H */
