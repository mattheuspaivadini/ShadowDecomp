/* KERNEL.XFF @ 0x025FC0 (212 B) - Sg2SepPause
 * Evidence: for i < 32 with status 1 or 2: DIntr(); saved = status; Sg2ModSetParam(handle, 0x80, 1, 0); Sg2ModSetParam(handle, 0x10, on, 0); status = on ? 3 : 4 (if/else, a ternary becomes movz); EIntr(). SEP records are 32 x 0x50 at .bss+0x971C0 (status +0x0, saved status +0x4, vab +0xC, sequencer handle +0x10).
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

int Sg2SepPause(unsigned int i, int on) {
    int intr;
    struct Sg2Sep *s;

    if (i < 32) {
        s = &D_kernel_bss_971C0[i];
        if (s->status == 1 || s->status == 2) {
            intr = DIntr();
            s->saved = s->status;
            Sg2ModSetParam(D_kernel_bss_971C0[i].mod, 0x80, 1, 0);
            Sg2ModSetParam(D_kernel_bss_971C0[i].mod, 0x10, on, 0);
            if (on) {
                s->status = 3;
            } else {
                s->status = 4;
            }
            if (intr) {
                EIntr();
            }
        }
    }
    return 0;
}
