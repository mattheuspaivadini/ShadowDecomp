/* KERNEL.XFF @ 0x01E7D8 (52 B) - sndVabInit
 * Evidence: clears bit 0 of word 0 of the twenty 0x1C-byte records at .bss+0x7D1D8 (the ~1 mask is materialised before the counter, as with a local). UNCONFIRMED: layout.
 */
struct SndVab {
    unsigned int flags;
    int id;
    int unk8;
    void *hd;
    void *bd;
    char pad[8];
};
extern struct SndVab D_kernel_bss_7D1D8[20];

void sndVabInit(void) {
    struct SndVab *v = D_kernel_bss_7D1D8;
    unsigned int mask = ~1;
    int i;

    for (i = 19; i >= 0; i--, v++) {
        v->flags &= mask;
    }
}
