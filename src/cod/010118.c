/* asm/cod/010118.s -> func_00110118 @ 0x00110118
 *   j func_0010F550 ; nop
 * A pure tail-call trampoline: the callee is declared `noreturn` so no frame
 * (and no `ra` save) is emitted - only the `j` and its delay slot. */
void func_0010F550(void) __attribute__((noreturn));

void func_00110118(void) {
    func_0010F550();
}
