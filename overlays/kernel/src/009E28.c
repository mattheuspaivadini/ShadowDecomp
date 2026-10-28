/* KERNEL.XFF @ 0x009E28 (104 B) - isysRelocateModuleObj
 * Evidence: `lw $2,44($16)` / `and $2,$2,$17` (lui 0x2000) test bit 0x20000000;
 * the set path is a sibcall `j func_0077D8` with `move $5,zero` in the exit
 * branch's delay slot, the clear path calls with a1=1 and then re-reads
 * `44($16)`, ORs the bit and stores it back (two loads of m->flags).
 * UNCONFIRMED: struct name, the callee's name/arity beyond (m, arg). The
 * `register int zero asm("$5")` pin only shapes the code: it keeps the
 * constant in the argument register so the exit branch's delay slot is filled
 * with the image's `move $5,zero` (a plain `0` makes gcc put `ld ra` there).
 */
struct ModuleObj {
    char pad0[0x2C];
    int flags;
};
void func_0077D8(struct ModuleObj *m, int arg);

void isysRelocateModuleObj(struct ModuleObj *m) {
    register int zero asm("$5") = 0;

    if (m->flags & 0x20000000) {
        func_0077D8(m, zero);
        return;
    }
    func_0077D8(m, 1);
    m->flags |= 0x20000000;
}
