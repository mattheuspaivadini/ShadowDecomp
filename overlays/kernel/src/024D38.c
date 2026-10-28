/* KERNEL.XFF @ 0x024D38 (164 B) - func_024D38 (static, no symbol in the shipped .symtab)
 * Evidence: MIDI all-sound-off for one channel: for every slot of the module class/channel (Sg2SlotFindSlotClassCh, last down) Sg2SlotSetAdsr(slot, 0, 8) then the slot key-off bit (Sg2SlotSetKeyOffBit(core, bit)). UNCONFIRMED: names; Ghidra FUN_00224d38.
 */
struct Sg2Mod {
    int vab;
    int cls;
};
extern unsigned char *D_kernel_bss_7F6CC;
extern struct Sg2Mod *D_kernel_bss_7F6D0;
int Sg2SlotFindSlotClassCh(int *out, int cls, int ch);
void Sg2SlotSetAdsr(int slot, int a, int b);
void Sg2SlotSetKeyOffBit(int core, unsigned int bits);

void func_024D38(void) {
    int list[48];
    int i;

    for (i = Sg2SlotFindSlotClassCh(list, D_kernel_bss_7F6D0->cls, D_kernel_bss_7F6CC[0] & 0xF) - 1; i >= 0; i--) {
        Sg2SlotSetAdsr(list[i], 0, 8);
        Sg2SlotSetKeyOffBit(list[i] >= 24, list[i] < 24 ? 1 << list[i] : 1 << (list[i] - 24));
    }
}
