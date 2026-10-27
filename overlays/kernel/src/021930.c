/* KERNEL.XFF @ 0x021930 (132 B) - Sg2ModMidiout1
 * Evidence: under DIntr/EIntr, stores the byte into the 512-byte MIDI ring at mod[id]+0x64 at index wr (+0x200 of the ring) and advances wr modulo 512. UNCONFIRMED: names.
 */
struct Sg2ModMidi {
    unsigned char buf[0x200];
    int wr;
};
struct Sg2Mod {
    char pad[0x64];
    struct Sg2ModMidi midi;
    char pad2[0x9B0 - 0x64 - 0x204];
};
extern struct Sg2Mod D_kernel_bss_7F6D8[];
int DIntr(void);
int EIntr(void);

void Sg2ModMidiout1(int id, unsigned char data) {
    int intr = DIntr();
    struct Sg2ModMidi *m = &D_kernel_bss_7F6D8[id].midi;

    m->buf[m->wr] = data;
    m->wr = (m->wr + 1) & 0x1FF;
    if (intr) {
        EIntr();
    }
}
