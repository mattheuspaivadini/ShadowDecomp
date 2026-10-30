/* GAMECORE.XFF @ 0x12B4A0 (12 B) - getSScriptWork
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .bss+0x22040) - returns the object address.
 */
extern char D_kernel_bss_22040[];

int getSScriptWork(void) {
    return (int)D_kernel_bss_22040;
}
