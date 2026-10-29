/* KERNEL.XFF @ 0x029320 (108 B) - Sg2SlotBlock
 * STATUS: NOT MATCHING, 24/27 words differ. Image shares (base+4)/(base+8) across the +0x00 and +0x10 sub-blocks and adds i*0xE0 last; tried
 * flat fields, two T3 sub-structs, char* base + off, serial-first/last orders (S72). Not in c_sources.txt.
 * Evidence: on the 0xE0-byte Sg2 slot [i] (.bss+0x97E30): flags = 0, +4 = vab, +0xC = -1, +0x14/+0x18 = -1 (+0x10 untouched), +8 = serial number from the counter at .bss+0x97E20 (incremented before the stores). Sibling of Sg2SlotSetBasicParam. UNCONFIRMED: names.
 */
struct Sg2SlotParam {
    int a;
    int b;
    int c;
};
struct Sg2Slot {
    unsigned int flags;
    int vab;
    int serial;
    int prog;
    struct Sg2SlotParam p;
    char pad1C[0xE0 - 0x1C];
};
extern int D_kernel_bss_97E20;
extern struct Sg2Slot D_kernel_bss_97E30[48];

void Sg2SlotBlock(int vab, int i) {
    int serial = D_kernel_bss_97E20;

    D_kernel_bss_97E20 = serial + 1;
    D_kernel_bss_97E30[i].flags = 0;
    D_kernel_bss_97E30[i].vab = vab;
    D_kernel_bss_97E30[i].p.c = -1;
    D_kernel_bss_97E30[i].p.b = -1;
    D_kernel_bss_97E30[i].prog = -1;
    D_kernel_bss_97E30[i].serial = serial;
}
