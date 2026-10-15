/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 21 [cc=29].
 * R1 wave3d: cc=29 varargs prologue order
 * The original .s stays in the build (asm/cod/0285C0.s); this C
 * draft (Session 8) is kept for the record. */
extern int D_00135C60[];   /* .data 0x00135C60: lui/%lo (non-small) */

int func_00129930(int ctx, char *fmt, int ap);

int func_001285C0(char *fmt, ...) {
    int f;

    f = D_00135C60[0];
    *(int *)(*(int *)(f + 8) + 0x54) = f;
    return func_00129930(*(int *)(f + 8), fmt, (int)__builtin_saveregs());
}
