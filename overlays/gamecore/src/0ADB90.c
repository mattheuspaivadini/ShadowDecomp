/* GAMECORE.XFF @ 0x0ADB90 (24 B) - Kite_InitKitePathPoint
 * Evidence: sqc2 $vf0 (VU0 store of 0,0,0,1) to a0, then words 0x10/0x14/0x18
 * UNCONFIRMED: vf0 store done as inline asm
 */
void Kite_InitKitePathPoint(char *p) {
    asm volatile("sqc2 $vf0, 0(%0)" :: "r"(p) : "memory");
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x10) = -1;
    *(int *)(p + 0x18) = -1;
}
