/* KERNEL.XFF @ 0x01DA30 (216 B) - isysJumpSubThread
 * MATCHING (xff_try, flags -G0 -fno-strict-aliasing, default cc). c_sources.txt line:
 *   01DA30 = src/01DA30.c -G0 -fno-strict-aliasing
 * Evidence: obj = isysGetThisSubThread(); jump table (.rodata+0x2930, 28 entries over type-6) maps types
 * 6,9,11,12,13,14,22,29,33 to &obj->0x20 and everything else to NULL (switch on the lbu at +8). Stores a to
 * [0]/[1], [4] = [3]+[5], publishes b/[4]/[1] to three .bss words, then switches stacks: the "la; lw" macro
 * pairs carry explicit nops (lui;nop;addiu;nop) so they are asm text, and the final `j 0x1D474` (a stripped
 * static) is part of the second asm with a0 loaded from the published word; the normal epilogue after it is dead.
 * UNCONFIRMED: field names, the .bss words' roles (stack top / arg / slot), callee name.
 */
extern int D_kernel_bss_7C3BC;
extern int D_kernel_bss_7C3C4;
extern int D_kernel_bss_7C3C8;
extern char *isysGetThisSubThread(void);

void isysJumpSubThread(int a, int b) {
    char *o = isysGetThisSubThread();
    int *t;

    switch (*(unsigned char *)(o + 8)) {
    case 6: case 9: case 11: case 12: case 13: case 14: case 22: case 29: case 33:
        t = (int *)(o + 32);
        break;
    default:
        t = 0;
        break;
    }
    t[1] = a;
    t[0] = a;
    t[4] = t[3] + t[5];
    D_kernel_bss_7C3C4 = b;
    D_kernel_bss_7C3BC = t[4];
    D_kernel_bss_7C3C8 = t[1];
    __asm__ volatile("lui $2,%hi(D_kernel_bss_7C3BC)\n\tnop\n\taddiu $2,$2,%lo(D_kernel_bss_7C3BC)\n\tnop\n\tlw $29,0($2)");
    __asm__ volatile("lui $2,%hi(D_kernel_bss_7C3C4)\n\tnop\n\taddiu $2,$2,%lo(D_kernel_bss_7C3C4)\n\tnop\n\tlw $4,0($2)\n\tj func_kernel_01D474");
}
