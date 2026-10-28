/* KERNEL.XFF @ 0x0072B8 (192 B) - Init_Shock
 * Evidence: two inlined init helpers with NULL guards on their static buffers: the shock table (.bss+0xD9D0, list of 2 at .bss+0xD9E0, published in .data+0x368 then cleared through it, +8 = 0), and a 16 x 0x40-byte pool (.bss+0xD9E8 / .bss+0xD9F0: count 16, first byte of each entry cleared; count 0 on a NULL guard). UNCONFIRMED: names.
 */
struct ShockTbl {
    int num;
    void **list;
    int unk8;
};
struct ShockPool {
    int num;
    char (*buf)[0x40];
};
extern struct ShockTbl D_kernel_bss_0D9D0;
extern void *D_kernel_bss_0D9E0[2];
extern struct ShockPool D_kernel_bss_0D9E8;
extern char D_kernel_bss_0D9F0[16][0x40];
extern struct ShockTbl *D_kernel_data_0368;

static inline void init_pool(struct ShockPool *p, char (*buf)[0x40], int n) {
    int i;

    if (p && buf) {
        p->num = n;
        p->buf = buf;
        for (i = 0; i < n; i++) {
            buf[i][0] = 0;
        }
    } else {
        p->num = 0;
    }
}

static inline void init_tbl(struct ShockTbl *t, void **list, int n) {
    int i;

    if (t && list) {
        t->list = list;
        t->num = n;
        D_kernel_data_0368 = t;
        for (i = 0; i < n; i++) {
            D_kernel_data_0368->list[i] = 0;
        }
        D_kernel_data_0368->unk8 = 0;
    }
}

void Init_Shock(void) {
    init_tbl(&D_kernel_bss_0D9D0, D_kernel_bss_0D9E0, 2);
    init_pool(&D_kernel_bss_0D9E8, D_kernel_bss_0D9F0, 16);
}
