/* KERNEL.XFF @ 0x0222A0 (56 B) - Sg2ModCheckSndOn
 * Evidence: for id >= 0 returns record[id].+0 != -1 (nor + sltu), else 0; records are 0x9B0 bytes at .bss+0x7F6D8 (id*5*31*16). UNCONFIRMED: names.
 */
struct Sg2Mod {
    int status;
    int unk4;
    int unk8;
    int unkC;
    int closeReq;
    char pad[0x9B0 - 0x14];
};
extern struct Sg2Mod D_kernel_bss_7F6D8[];

int Sg2ModCheckSndOn(int id) {
    if (id >= 0) {
        return D_kernel_bss_7F6D8[id].status != -1;
    }
    return 0;
}
