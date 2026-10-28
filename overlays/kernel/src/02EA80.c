/* KERNEL.XFF @ 0x02EA80 (40 B) - func_02EA80 (static, no symbol in the shipped .symtab)
 * Evidence: returns table + ofs[i] / 4 words, ofs[] at +8 (EQ filter table entry). UNCONFIRMED: names.
 */
struct FiltTbl {
    int magic;
    int num;
    int ofs[1];
};

int *func_02EA80(struct FiltTbl *t, int i) {
    return (int *)t + *(t->ofs + i) / 4;
}
