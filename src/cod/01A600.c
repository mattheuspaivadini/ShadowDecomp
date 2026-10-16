/* asm/cod/01A600.s -> sceMc2iChangeThreadPriority.
 * sceMc2iChangeThreadPriority (SHN_ABS)
 * MATCHED (Session 12). */
extern int D_00151E20[];

int iChangeThreadPriority(int a, int b);

int sceMc2iChangeThreadPriority(int a0) {
    if (a0 > 0) {
        iChangeThreadPriority(D_00151E20[0], a0);
        return 0;
    }
    return 0x81010016;
}
