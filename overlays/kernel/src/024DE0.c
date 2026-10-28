/* KERNEL.XFF @ 0x024DE0 (148 B) - func_024DE0 (static, no symbol in the shipped .symtab)
 * Evidence: MIDI all-notes-off for one channel: Sg2SlotFindSlotClassCh(list, module cls, msg[0] & 0xF) into a 48-int list, then Sg2SlotSetKeyOffBit(core, bit) per slot from the last down (as all_keyoff). UNCONFIRMED: names; Ghidra FUN_00224de0.
 */
struct Sg2Mod {
    int vab;
    int cls;
};
extern unsigned char *D_kernel_bss_7F6CC;
extern struct Sg2Mod *D_kernel_bss_7F6D0;
int Sg2SlotFindSlotClassCh(int *out, int cls, int ch);
void Sg2SlotSetKeyOffBit(int core, unsigned int bits);

void func_024DE0(void) {
    int list[48];
    int i;

    for (i = Sg2SlotFindSlotClassCh(list, D_kernel_bss_7F6D0->cls, D_kernel_bss_7F6CC[0] & 0xF) - 1; i >= 0; i--) {
        Sg2SlotSetKeyOffBit(list[i] >= 24, list[i] < 24 ? 1 << list[i] : 1 << (list[i] - 24));
    }
}
