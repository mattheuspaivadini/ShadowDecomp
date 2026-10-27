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
int DIntr(void);
int EIntr(void);
void Sg2ModMidiout1(int id, unsigned char data);

int Sg2SepStop(unsigned int i) {
    int intr;
    struct Sg2Sep *s;

    if (i < 32) {
        s = &D_kernel_bss_971C0[i];
        if (s->status > 0) {
            intr = DIntr();
            s->status = 2;
            s->vab = -1;
            Sg2ModMidiout1(D_kernel_bss_971C0[i].mod, 0xFF);
            Sg2ModMidiout1(D_kernel_bss_971C0[i].mod, 0x40);
            Sg2ModMidiout1(D_kernel_bss_971C0[i].mod, 0xF7);
        }
        if (intr) {
            EIntr();
        }
    }
    return 0;
}
