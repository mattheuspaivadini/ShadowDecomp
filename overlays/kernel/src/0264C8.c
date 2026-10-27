/* KERNEL.XFF @ 0x025E50 (184 B) - Sg2SepStop
 * Evidence: for i < 32 with status > 0: DIntr(); status = 2, vab = -1; Sg2ModMidiout1(handle, 0xFF / 0x40 / 0xF7); EIntr() when interrupts were on (the test sits outside the inner if, as in the image); returns 0. SEP records are 32 x 0x50 at .bss+0x971C0 (status +0x0, saved status +0x4, vab +0xC, sequencer handle +0x10).
 * The record pointer is taken inside the range check and the handle is read through the array index: that gives the image's (i*0x50+0x10)+base address held across the calls. UNCONFIRMED: field names, Sg2ModSetParam prototype.
 */
struct Sg2Sep {
    int status;
    int saved;
    int unk8;
    int vab;
    int mod;
    char pad[0x50 - 0x14];
};
extern struct Sg2Sep D_kernel_bss_971C0[32];
int vab_check_alive(int id);
int vab_set_semastervol(int id, int vol);
int Sg2ModSetParam(int id, int param, int value, int unk);

int Sg2SepMasterVol(int vab, int vol) {
    struct Sg2Sep *s;
    int i;

    if (!vab_check_alive(vab)) {
        return -1;
    }
    vab_set_semastervol(vab, vol);
    s = D_kernel_bss_971C0;
    for (i = 0; i < 32; i++, s++) {
        if (s->vab == vab) {
            Sg2ModSetParam(s->mod, 2, vol, 0);
        }
    }
    return vol;
}
