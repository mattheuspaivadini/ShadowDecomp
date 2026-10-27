/* KERNEL.XFF @ 0x026230 (64 B) - Sg2SepCheckSndOn
 * Evidence: for id < 32 calls Sg2ModCheckSndOn(record[id].+0x10) but discards the result and always returns 0 (as in the original).
 */
struct Sg2Sep {
    int status;
    int unk4;
    int unk8;
    int unkC;
    int mod;
    char pad[0x50 - 0x14];
};
extern struct Sg2Sep D_kernel_bss_971C0[32];
int Sg2ModCheckSndOn(int id);

int Sg2SepCheckSndOn(unsigned int id) {
    if (id < 32) {
        Sg2ModCheckSndOn(D_kernel_bss_971C0[id].mod);
    }
    return 0;
}
