/* KERNEL.XFF @ 0x02BF08 (88 B) - Sg2SmfpCont
 * Evidence: for id >= 0 sets the SMF record status (.bss+0x9A880 [id]) to 2; Sg2ModSetParam(record.mod, 0x40, 0, 0) unconditionally (index added as offset + base); returns 0.
 */
struct Sg2Smfp {
    int status;
    int unk4;
    int mod;
    int vab;
    char pad[0x80 - 0x10];
};
extern struct Sg2Smfp D_kernel_bss_9A880[8];
int Sg2ModSetParam(int mod, int type, int a, int b);

int Sg2SmfpCont(int id) {
    if (id >= 0) {
        D_kernel_bss_9A880[id].status = 2;
    }
    Sg2ModSetParam((&D_kernel_bss_9A880[0] + id)->mod, 0x40, 0, 0);
    return 0;
}
