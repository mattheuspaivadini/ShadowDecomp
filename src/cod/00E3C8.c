/* asm/cod/00E3C8.s -> sceSifLoadFileReset.
 * sceSifLoadFileReset cc=29
 * MATCHED (Session 12). */
int func_001283D0(void *dst, int val, int size);

extern int D_00132330[];
extern char D_001475A8[];

int sceSifLoadFileReset(void) {
    D_00132330[0] = -1;
    func_001283D0(D_001475A8, 0, 4);
    return 0;
}
