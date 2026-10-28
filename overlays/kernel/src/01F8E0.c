/* KERNEL.XFF @ 0x01F8E0 (84 B) - Sg2CtrlInit
 * Evidence: the 16 tick-proc records (8 bytes at .bss+0x7F540) get func = the empty static at .text+0x1F690 and arg 0; Sg2CtrlSetTickTime(0); returns 0. UNCONFIRMED: field names.
 */
struct Sg2CtrlTick { void (*func)(void); int unk4; };
extern struct Sg2CtrlTick D_kernel_bss_7F540[16];
void func_01F690(void);
int Sg2CtrlSetTickTime(int t);
int Sg2CtrlInit(void) {
 int i;
 for (i = 0; i < 16; i++) { D_kernel_bss_7F540[i].func = func_01F690; D_kernel_bss_7F540[i].unk4 = 0; }
 Sg2CtrlSetTickTime(0);
 return 0;
}
