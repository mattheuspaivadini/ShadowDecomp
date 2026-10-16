/* asm/cod/0000C0.s -> func_001000C0 @ 0x001000C0
 *   j func_001101D8 ; daddu $a0,$zero,$zero
 * Tail-call trampoline with a0 = 0; the callee is declared `noreturn`. */
void Exit(int a0) __attribute__((noreturn));

void func_001000C0(void) {
    Exit(0);
}
