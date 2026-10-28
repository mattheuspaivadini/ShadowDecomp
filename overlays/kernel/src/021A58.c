/* KERNEL.XFF @ 0x021A58 (256 B) - Sg2ModMidiout
 * Evidence: under DIntr/EIntr (EIntr tail call) appends len bytes to the 0x200-byte MIDI ring of module [i] (0x9B0-byte records at .bss+0x7F73C, write position +0x200), splitting the copy in two memcpy calls at the wrap. UNCONFIRMED: names.
 */
struct ModRing {
    unsigned char buf[0x200];
    int wpos;
    char pad[0x9B0 - 0x204];
};
extern struct ModRing D_kernel_bss_7F73C[];
int DIntr(void);
int EIntr(void);
void *memcpy(void *d, const void *s, unsigned int n);

void Sg2ModMidiout(int mod, int len, unsigned char *data) {
    int intr = DIntr();
    struct ModRing *r = &D_kernel_bss_7F73C[mod];
    int room = 0x200 - r->wpos;
    int over = room - len;

    if (over >= 0) {
        memcpy(r->buf + r->wpos, data, len);
        r->wpos = (r->wpos + len) & 0x1FF;
    } else {
        memcpy(r->buf + r->wpos, data, room);
        memcpy(r->buf, data + room, -over);
        r->wpos = -over;
    }
    if (intr) {
        EIntr();
    }
}
