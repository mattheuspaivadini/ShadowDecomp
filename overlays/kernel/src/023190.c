/* KERNEL.XFF @ 0x023190 (52 B) - func_023190 (static, no symbol in the shipped .symtab)
 * Evidence: MIDI note-off handler: Sg2SlotModKeyOff(current module (.bss+0x7F6D0)->cls, msg[0] & 0xF (channel), msg[1] (note)) with the message pointer at .bss+0x7F6CC. UNCONFIRMED: names; Ghidra FUN_00223190.
 */
struct Sg2Mod {
    int status;
    int cls;
};
extern unsigned char *D_kernel_bss_7F6CC;
extern struct Sg2Mod *D_kernel_bss_7F6D0;
void Sg2SlotModKeyOff(int cls, int id, int sub);

void func_023190(void) {
    Sg2SlotModKeyOff(D_kernel_bss_7F6D0->cls, D_kernel_bss_7F6CC[0] & 0xF, D_kernel_bss_7F6CC[1]);
}
