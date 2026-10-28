/* KERNEL.XFF @ 0x029780 (236 B) - Sg2SlotSetBasicParam
 * Evidence: on the 0xE0-byte Sg2 slot [i] (.bss+0x97E30): flags = 1, +4 = vab, +0xC = prog, +0x10/+0x14/+0x18 = three parameters, +8 = serial number from the counter at .bss+0x97E20 (incremented after the stores); then the statics .text+0x2A978 and .text+0x2AA50 get (core = i >= 24, voice bit i mod 24). UNCONFIRMED: names.
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
void func_02A978(int core, unsigned int mask);
void func_02AA50(int core, unsigned int mask);

#define CORE(i) ((i) >= 24)
#define VMASK(i) ((i) < 24 ? 1 << (i) : 1 << ((i) - 24))

void Sg2SlotSetBasicParam(int vab, int i, int prog, int a, int b, int c) {
    int serial = D_kernel_bss_97E20;

    D_kernel_bss_97E30[i].flags = 1;
    D_kernel_bss_97E30[i].vab = vab;
    D_kernel_bss_97E30[i].prog = prog;
    D_kernel_bss_97E30[i].p.a = a;
    D_kernel_bss_97E30[i].p.b = b;
    D_kernel_bss_97E30[i].p.c = c;
    D_kernel_bss_97E30[i].serial = serial;
    D_kernel_bss_97E20 = serial + 1;
    func_02A978(CORE(i), VMASK(i));
    func_02AA50(CORE(i), VMASK(i));
}
