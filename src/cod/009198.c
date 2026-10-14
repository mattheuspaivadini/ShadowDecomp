/* func_00109198 @ 0x00109198 (0x24 bytes): call func_00112B98, clear
 * D_00132288 (.data, absolute). */
void func_00112B98(void);

extern __attribute__((section(".data"))) int D_00132288;

void func_00109198(void) {
    func_00112B98();
    D_00132288 = 0;
}
