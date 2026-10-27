/* KERNEL.XFF @ 0x0222D8 (48 B) - Sg2ModClose
 * Evidence: for id >= 0 sets record[id].+0x10 = 1 (0x9B0-byte records at .bss+0x7F6D8); returns 0. UNCONFIRMED: names.
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

int Sg2ModClose(int id) {
    if (id >= 0) {
        D_kernel_bss_7F6D8[id].closeReq = 1;
    }
    return 0;
}
