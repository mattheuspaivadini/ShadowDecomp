/* asm/cod/01C3B0.s -> func_0011C3B0.
 * Two separate error returns (one per failing call) instead of one || test: jump2 cross-jumps them back into one block, but at global-alloc time the extra *err reference gives err priority over idx*0x898 (s3/s4 roles) (Session 26).
 * MATCHED. */
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
        if (func_0011C320(idx) == 0) {
            *err = 0x8101006F;
            return 0;
        }
        if (_sceMcpReadClust(idx, D_0015DF48[idx].fat, clust, 1) == 0) {
            *err = 0x8101006F;
            return 0;
        }
        D_0015DF48[idx].cached = clust;
    }
    clust = D_0015DF48[idx].fat[off];
    *err = 0;
    return clust;
}
