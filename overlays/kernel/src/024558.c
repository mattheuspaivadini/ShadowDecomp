/* KERNEL.XFF @ 0x024558 (156 B) - func_024558 (static, no symbol in the shipped .symtab)
 * Evidence: as func_024418 with channel field +0x58 and Sg2SlotSetLfoVolDepth. UNCONFIRMED: controller number; Ghidra FUN_00224558.
 */
struct Sg2ModChan {
    char pad0[0x58];
    int val;
    char pad[0x70 - 0x58 - 4];
};
struct Sg2Mod {
    int vab;
    int cls;
    char pad8[0x2B0 - 8];
    struct Sg2ModChan ch[16];
};
extern unsigned char *D_kernel_bss_7F6CC;
extern struct Sg2Mod *D_kernel_bss_7F6D0;
int Sg2SlotFindSlotClassCh(int *out, int cls, int ch);
void Sg2SlotSetLfoVolDepth(int slot, int value);

void func_024558(void) {
    int list[48];
    struct Sg2Mod *m = D_kernel_bss_7F6D0;
    int ch = D_kernel_bss_7F6CC[0] & 0xF;
    int i;

    m->ch[ch].val = D_kernel_bss_7F6CC[2];
    for (i = Sg2SlotFindSlotClassCh(list, m->cls, ch) - 1; i >= 0; i--) {
        Sg2SlotSetLfoVolDepth(list[i], D_kernel_bss_7F6CC[2]);
    }
}
