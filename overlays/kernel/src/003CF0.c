/* KERNEL.XFF @ 0x003CF0 (32 B) - func_003CF0 (static, no symbol in the shipped .symtab)
 * Evidence: tail call to the static at .text+0x2FF0 as (a0, 0, a1, -1). UNCONFIRMED: name and argument meaning; Ghidra FUN_00203cf0.
 */
void func_002FF0(void *a, int b, void *c, int d);

void func_003CF0(void *a, void *c) {
    func_002FF0(a, 0, c, -1);
}
