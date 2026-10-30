/* GAMECORE.XFF @ 0x124168 (36 B) - initAttackWaistIKWork
 * Evidence: stores $vf0, 0x0($a2), $vf0, 0x0($v0), $zero, 0x20($a2), $f0, 0x28($a2), $zero, 0x24($a2)
 
 */
/* UNCONFIRMED: same shape as initAimIKWork (VU0 zero fill via inline asm). */
void initAttackWaistIKWork(void *a, void *b, char *p) {
    asm volatile("sqc2 $vf0, 0(%0)" :: "r"(p) : "memory");
    asm volatile("sqc2 $vf0, 0(%0)" :: "r"(p + 0x10) : "memory");
    *(int *)(p + 0x20) = 0;
    *(int *)(p + 0x24) = 0;
    *(float *)(p + 0x28) = 1.0f;
}
