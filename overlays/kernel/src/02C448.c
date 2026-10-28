/* KERNEL.XFF @ 0x02C448 (152 B) - Sg2SmfpMidiOut
 * Evidence: for id >= 0: -1 when the SMF player record [id] (.bss+0x9A880) is idle; else appends its channel byte (+8), n, and n data bytes to the MIDI-out byte buffer at .bss+0x9B4A0 with the index at .bss+0x9BCA0 (reloaded per byte; count-down copy of n); returns 0. UNCONFIRMED: names.
 */
struct Sg2Smfp {
    int status;
    int unk4;
    unsigned char ch;
    char pad9[0x80 - 9];
};
extern struct Sg2Smfp D_kernel_bss_9A880[8];
extern unsigned char D_kernel_bss_9B4A0[];
extern int D_kernel_bss_9BCA0;
int Sg2SmfpMidiOut(int id, int n, unsigned char *data) {
 int i;
 if (id >= 0) {
 if (D_kernel_bss_9A880[id].status == 0) return -1;
 D_kernel_bss_9B4A0[D_kernel_bss_9BCA0++] = D_kernel_bss_9A880[id].ch;
 D_kernel_bss_9B4A0[D_kernel_bss_9BCA0++] = n;
 for (i = n; i != 0; i--) D_kernel_bss_9B4A0[D_kernel_bss_9BCA0++] = *data++;
 }
 return 0;
}
