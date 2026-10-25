/* KERNEL.XFF @ 0x026150 (108 B) - Sg2SepVabStopSndOff
 * Evidence: when vab_check_alive(vab), the static stopper at .text+0x25F08 is called for every SEP record (32 x 0x50 at .bss+0x971C0) whose +0xC equals vab (record-pointer loop); returns 0.
 */
struct Sg2Sep {
    int status;
    int unk4;
    int unk8;
    int vab;
    char pad[0x50 - 0x10];
};
extern struct Sg2Sep D_kernel_bss_971C0[32];
int vab_check_alive(int id);
void func_025F08(int id);

int Sg2SepVabStopSndOff(int vab) {
    struct Sg2Sep *s;
    int i;

    if (vab_check_alive(vab)) {
        s = D_kernel_bss_971C0;
        for (i = 0; i < 32; i++, s++) {
            if (s->vab == vab) {
                func_025F08(i);
            }
        }
    }
    return 0;
}
