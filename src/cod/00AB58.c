/* asm/cod/00AB58.s -> sceFsReset.
 * sceFsReset: D_00132314 .data attribute
 * MATCHED (Session 12). */
int func_001283D0(void *dst, int val, int size);

extern __attribute__((section(".data"))) int D_00132314;
extern char D_001470E8[];

int sceFsReset(void) {
    D_00132314 = 0;
    func_001283D0(D_001470E8, 0, 4);
    return 0;
}
