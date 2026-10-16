/* asm/cod/01A5C8.s -> sceMc2ChangeThreadPriority.
 * sceMc2ChangeThreadPriority (SHN_ABS)
 * MATCHED (Session 12). */
extern int D_00151E20[];

int ChangeThreadPriority(int a, int b);

int sceMc2ChangeThreadPriority(int a0) {
    if (a0 > 0) {
        ChangeThreadPriority(D_00151E20[0], a0);
        return 0;
    }
    return 0x81010016;
}
