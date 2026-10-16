/* func_00109198 @ 0x00109198 (0x24 bytes): call func_00112B98, clear
 * D_00132288 (.data, absolute). */
void sceSifExitCmd(void);

extern __attribute__((section(".data"))) int D_00132288;

void sceSifExitRpc(void) {
    sceSifExitCmd();
    D_00132288 = 0;
}
