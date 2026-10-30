/* GAMECORE.XFF @ 0x124190 (52 B) - nico_attackIK_optBone
 * Evidence: stores $ra, 0x10($sp); loads $a3, 0x14($v0), $a2, 0x0($v0), $ra, 0x10($sp); relocs <.bss>; calls GetMotionNodeQuaternionPos; frame
 
 */
void GetMotionNodeQuaternionPos(void *work, void *out, int a, int b, int c);
extern char D_kernel_bss_2010[];

/* UNCONFIRMED: the stack local is a 16-byte quaternion output buffer. */
void nico_attackIK_optBone(char *p) {
    int local[4];
    GetMotionNodeQuaternionPos(D_kernel_bss_2010, local, *(int *)p,
                               *(int *)(p + 0x14), 0);
}
