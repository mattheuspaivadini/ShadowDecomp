/* KERNEL.XFF @ 0x0219B8 (160 B) - Sg2ModMidiout1Exclusive
 * Evidence: under DIntr/EIntr (EIntr as a tail call) copies bytes up to and including 0xF7 (SysEx end) into the 0x200-byte ring at +0x64 of the module record [id] (0x9B0 bytes at .bss+0x7F6D8), write index at +0x264 wrapped with & 0x1FF. UNCONFIRMED: field names.
 */
struct Sg2ModEx {
    unsigned char buf[0x200];
    int wr;
};
struct Sg2Mod {
    int status;
    int cls;
    char pad8[0x64 - 8];
    struct Sg2ModEx ex;
    char pad268[0x9B0 - 0x268];
};
extern struct Sg2Mod D_kernel_bss_7F6D8[32];
int DIntr(void);
int EIntr(void);

void Sg2ModMidiout1Exclusive(int id, unsigned char *data) {
    int intr = DIntr();
    struct Sg2ModEx *ex = &D_kernel_bss_7F6D8[id].ex;

    do {
        ex->buf[ex->wr] = *data;
        ex->wr = (ex->wr + 1) & 0x1FF;
    } while (*data++ != 0xF7);
    if (intr) {
        EIntr();
    }
}
