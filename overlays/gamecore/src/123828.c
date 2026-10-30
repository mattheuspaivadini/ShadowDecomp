/* GAMECORE.XFF @ 0x123828 (36 B) - initAimIKWork
 * Evidence: stores $vf0, 0x0($a2), $vf0, 0x0($v0), $zero, 0x20($a2), $f0, 0x28($a2), $zero, 0x24($a2)
 
 */
/* UNCONFIRMED: 32-byte zero fill is two VU0 `sqc2 $vf0` stores (inline asm),
 * the rest are plain word stores at 0x20/0x24 and 1.0f at 0x28.
 */
void initAimIKWork(void *a, void *b, char *p) {
    asm volatile("sqc2 $vf0, 0(%0)" :: "r"(p) : "memory");
    asm volatile("sqc2 $vf0, 0(%0)" :: "r"(p + 0x10) : "memory");
    *(int *)(p + 0x20) = 0;
    *(int *)(p + 0x24) = 0;
    *(float *)(p + 0x28) = 1.0f;
}
