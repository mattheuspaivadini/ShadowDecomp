/* KERNEL.XFF @ 0x02DD58 (32 B) - func_02DD58 (static, no symbol in the shipped .symtab)
 * Evidence: memset(t->tbl (+4), 0, n * 4) as a tail call. UNCONFIRMED: struct names; Ghidra FUN_0022dd58.
 */
struct Sg2Tbl {
    int num;
    int *tbl;
};
void *memset(void *p, int c, unsigned int n);

void func_02DD58(struct Sg2Tbl *t, int n) {
    memset(t->tbl, 0, n * 4);
}
