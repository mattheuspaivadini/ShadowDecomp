/* GAMECORE.XFF @ 0x00BFF0 (12 B) - GetPlayerControlButtonContext
 * Shape `ret-addr` recovered by tools/xff_shapes.py and proved by
 * recompiling it byte-exactly (relocations masked).
 * Evidence: `lui $r2` + `jr $ra` + delay `addiu` (HI16/LO16 .data+0x314) - returns the object address.
 */
extern char gcGlobalVar[];

int GetPlayerControlButtonContext(void) {
    return (int)gcGlobalVar;
}
