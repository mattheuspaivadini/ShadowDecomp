/* KERNEL.XFF @ 0x026200 (48 B) - Sg2SepStatus
 * Evidence: returns word 0 of the 80-byte record [id] at .bss+0x971C0 for id < 32 (unsigned), else 0.
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

int Sg2SepStatus(unsigned int id) {
    if (id < 32) {
        return D_kernel_bss_971C0[id].status;
    }
    return 0;
}
