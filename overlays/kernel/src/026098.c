/* KERNEL.XFF @ 0x026098 (184 B) - Sg2SepCont
 * Evidence: for i < 32 with status 3 or 4: DIntr(); Sg2ModSetParam(handle, 0x80, 0, 0); Sg2ModSetParam(handle, 0x10, 0, 0); status = saved; EIntr(). SEP records are 32 x 0x50 at .bss+0x971C0 (status +0x0, saved status +0x4, vab +0xC, sequencer handle +0x10).
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
int DIntr(void);
int EIntr(void);
int Sg2ModSetParam(int id, int param, int value, int unk);

int Sg2SepCont(unsigned int i) {
    int intr;
    struct Sg2Sep *s;

    if (i < 32) {
        s = &D_kernel_bss_971C0[i];
        if (s->status == 3 || s->status == 4) {
            intr = DIntr();
            Sg2ModSetParam(D_kernel_bss_971C0[i].mod, 0x80, 0, 0);
            Sg2ModSetParam(D_kernel_bss_971C0[i].mod, 0x10, 0, 0);
            s->status = s->saved;
            if (intr) {
                EIntr();
            }
        }
    }
    return 0;
}
