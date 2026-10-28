/* KERNEL.XFF @ 0x01BB58 (16 B) - func_01BB58 (static, no symbol in the shipped .symtab)
 * Evidence: obj +0x14 = *sel ? b : a (movn). UNCONFIRMED: names; Ghidra merges it into a neighbour.
 */
struct LetterObj {
    char pad[0x14];
    int value;
};

void func_01BB58(struct LetterObj *o, int a, int b, int *sel) {
    o->value = *sel ? b : a;
}
