/* GAMECORE.XFF @ 0x112F50 (28 B) - resetVelocityWormCtrlWork
 * Evidence: zero stores 0x98/0x9C/0xB4 and sqc2 vf0 at a1+0xA0 (inline asm)
 * UNCONFIRMED: field names/types guessed from offsets
 */
void resetVelocityWormCtrlWork(int a, char *p) {
    *(int *)(p + 0x9C) = 0;
    *(int *)(p + 0x98) = 0;
    *(int *)(p + 0xB4) = 0;
    asm volatile("sqc2 $vf0, 0(%0)" :: "r"(p + 0xA0) : "memory");
}
