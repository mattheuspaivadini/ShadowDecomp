/* KERNEL.XFF @ 0x02BF88 (56 B) - Sg2SmfpCheckSndOn
 * Evidence: for id >= 0, sibling Sg2ModCheckSndOn(record[id].+8) (128-byte records at .bss+0x9A880), else 0.
 */
struct Sg2Smfp {
    int status;
    int unk4;
    int mod;
    char pad[0x80 - 0xC];
};
extern struct Sg2Smfp D_kernel_bss_9A880[];
int Sg2ModCheckSndOn(int id);

int Sg2SmfpCheckSndOn(int id) {
    if (id >= 0) {
        return Sg2ModCheckSndOn(D_kernel_bss_9A880[id].mod);
    }
    return 0;
}
