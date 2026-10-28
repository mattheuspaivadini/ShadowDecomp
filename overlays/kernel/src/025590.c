/* KERNEL.XFF @ 0x025590 (224 B) - func_025590 (static, no symbol in the shipped .symtab)
 * Evidence: MIDI meta/controller dispatch on msg[1] (.bss+0x7F6CC): 0x2F all_keyoff, 0x3F Sg2ModClose, 0x40 all_keyoff + Sg2ModClose, 0x41 all_soundoff + Sg2ModClose, each on the current module id (.bss+0x7F6C8), as tail calls with explicit returns. UNCONFIRMED: event meaning; Ghidra FUN_00225590 (0xE0 bytes: Ghidra stops before the shared return block).
 */
extern unsigned char *D_kernel_bss_7F6CC;
extern int D_kernel_bss_7F6C8;
void all_keyoff(int id);
void all_soundoff(int id);
int Sg2ModClose(int id);

void func_025590(void) {
    switch (D_kernel_bss_7F6CC[1]) {
    case 0x2F:
        all_keyoff(D_kernel_bss_7F6C8);
        return;
    case 0x3F:
        Sg2ModClose(D_kernel_bss_7F6C8);
        return;
    case 0x40:
        all_keyoff(D_kernel_bss_7F6C8);
        Sg2ModClose(D_kernel_bss_7F6C8);
        return;
    case 0x41:
        all_soundoff(D_kernel_bss_7F6C8);
        Sg2ModClose(D_kernel_bss_7F6C8);
        return;
    }
}
