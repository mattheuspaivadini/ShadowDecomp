/* KERNEL.XFF @ 0x02F838 (40 B) - Sg2ExPcmOutputAutoFilterCtrl
 * Evidence: stores on/off to word 0 of the 0xC4-byte filter record [f] at .bss+0x9BE3C (f * 49 * 4). UNCONFIRMED: names.
 */
struct PcmFilt {
    int enable;
    char pad[0xC0];
};
extern struct PcmFilt D_kernel_bss_9BE3C[];

void Sg2ExPcmOutputAutoFilterCtrl(int f, int on) {
    D_kernel_bss_9BE3C[f].enable = on;
}
