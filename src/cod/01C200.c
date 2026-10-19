/* asm/cod/01C200.s -> func_0011C200.
 * Session 8 draft (never promoted), byte-exact at cc=29: cached directory-index lookup over D_0015DF48 (0x898-byte per-port cache, cf. 01C3B0) (Session 28).
 * MATCHED. */
struct Mc2SysInfo {
    unsigned char pad00[0x50];
    int ifc_list[32];
    unsigned char padD0[0x184 - 0xD0];
};

struct McpCache {
    int table[0x200];
    int unk800;
    int cached_idx;
    unsigned char pad808[0x898 - 0x808];
};

extern struct Mc2SysInfo gSceMc2SysInfo[];
extern struct McpCache D_0015DF48[];

int _sceMcpReadClust(int port, void *buf, int clust, int count);

int func_0011C200(int port, int clust, int *err) {
    struct Mc2SysInfo *sys = &gSceMc2SysInfo[port];
    int idx = clust / 0x10000;
    int off = (clust / 0x100) - (idx * 0x100);
    int val;

    if (D_0015DF48[port].cached_idx != idx) {
        if (_sceMcpReadClust(port, &D_0015DF48[port], sys->ifc_list[idx], 1) == 0) {
            *err = 0x8101006F;
            return 0;
        }
        D_0015DF48[port].cached_idx = idx;
    }

    val = D_0015DF48[port].table[off];
    if (val < 0) {
        *err = 0x81019001;
        return 0;
    }
    *err = 0;
    return val;
}
