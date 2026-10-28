/* KERNEL.XFF @ 0x024E80 (56 B) - func_024E80 (static, no symbol in the shipped .symtab)
 * Evidence: dispatches msg[1] (message pointer .bss+0x7F6CC) through the function table at .data+0xBA8 (jalr). UNCONFIRMED: names; Ghidra FUN_00224e80.
 */
extern unsigned char *D_kernel_bss_7F6CC;
extern void (*D_kernel_data_0BA8[])(void);

void func_024E80(void) {
    D_kernel_data_0BA8[D_kernel_bss_7F6CC[1]]();
}
