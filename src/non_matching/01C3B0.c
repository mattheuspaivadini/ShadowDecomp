/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 9 [cc=29].
 * typed FAT-cache record + reused clust local; residual = $s3/$s4 roles of err vs idx*0x898.
 * The original .s stays in the build (asm/cod/01C3B0.s). */
struct F { char pad00[0x400]; int fat[0x100]; int cached; char pad804[0x898 - 0x804]; };
extern struct F D_0015DF48[];
int func_0011C200(int idx, int n, int *err);
int func_0011C320(int idx);
int _sceMcpReadClust(int idx, void *buf, int clust, int n);

int func_0011C3B0(int idx, int n, int *err) {
    int off;
    int clust;
    off = n % 256;
    clust = func_0011C200(idx, n, err);
    if (*err) return 0;
    if (D_0015DF48[idx].cached != clust) {
        if (func_0011C320(idx) == 0 || _sceMcpReadClust(idx, D_0015DF48[idx].fat, clust, 1) == 0) {
            *err = 0x8101006F;
            return 0;
        }
        D_0015DF48[idx].cached = clust;
    }
    clust = D_0015DF48[idx].fat[off];
    *err = 0;
    return clust;
}
