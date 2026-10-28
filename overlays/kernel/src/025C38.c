/* KERNEL.XFF @ 0x025C38 (536 B) - Sg2SepPlaySelectCore
 * Evidence: DIntr() first, then vab_check_alive() gates the body (return -4).
 * The free-record search walks the 32 x 0x50 SEP records at .bss+0x971C0
 * starting at the cursor .bss+0x97BC0 with a signed `(cursor + i) % 32`
 * (`slti`/`movn`/`sra`/`sll`/`subu` idiom); a record with status == 0 is
 * claimed (unk8 = cursor, cursor + 1 written back) and the index becomes the
 * return value (-3 when nothing is free).  Bit 0x10000 of the second argument
 * is cleared and Sg2SepSetParam(idx, 0x200, 1, 0) is issued *before* the
 * call arguments are built (that order is what the schedule expects).
 * vab_get_seseq() -> error -1, Sg2ModOpenSe() -> error -2; (+0x0C) = vab,
 * (+0x10) = mod, (+0x40)/(+0x3C) = seseq, (+0x20) = 480.0 / (double) tick
 * (litodp + dpdiv, signed conversion, no 2^32 fixup), (+0x28)/(+0x30) = 0,
 * (+0x38) = 0, (+0x00) = 1, (+0x18) = arg2, (+0x04) = 0, (+0x14) = arg1, and
 * func_025B18(vab, a1, a2, a3) when a3 != 0. Needs -g0.
 * UNCONFIRMED: field/parameter names, func_025B18.
 */
struct Sg2Sep {
    int status;         /* 0x00 */
    int saved;          /* 0x04 */
    int unk8;           /* 0x08 */
    int vab;            /* 0x0C */
    int mod;            /* 0x10 */
    int unk14;          /* 0x14 */
    int unk18;          /* 0x18 */
    int unk1C;          /* 0x1C */
    double d20;         /* 0x20 */
    double d28;         /* 0x28 */
    double d30;         /* 0x30 */
    int unk38;          /* 0x38 */
    int unk3C;          /* 0x3C */
    int seseq;          /* 0x40 */
    char pad44[0x0C];
};
extern struct Sg2Sep D_kernel_bss_971C0[32];
extern int D_kernel_bss_97BC0;
int DIntr(void);
int EIntr(void);
int vab_check_alive(int vab);
int vab_get_seseq(int vab, int a1, int a2);
int Sg2ModOpenSe(int vab, int a4);
int Sg2CtrlGetTickMode(void);
int Sg2SepSetParam(int sep, int param, int value, int unk);
void func_025B18(int vab, int a1, int a2, int a3);

int Sg2SepPlaySelectCore(int vab, int a1, int a2, int a3, int a4) {
    int intr;
    int i;
    int idx;
    int cursor;
    int ret;
    int found;
    int *cur;
    int seseq;
    int mod;
    struct Sg2Sep *p;

    intr = DIntr();
    if (!vab_check_alive(vab)) {
        ret = -4;
        goto done;
    }
    cur = &D_kernel_bss_97BC0;
    cursor = *cur;
    found = -1;
    for (i = 0; i < 0x20; i++) {
        idx = (cursor + i) % 32;
        if (D_kernel_bss_971C0[idx].status == 0) {
            D_kernel_bss_971C0[idx].unk8 = cursor;
            *cur = cursor + 1;
            found = idx;
            break;
        }
    }
    if (found == -1) {
        ret = -3;
        goto done;
    }
    ret = found;
    p = &D_kernel_bss_971C0[ret];
    if (a2 & 0x10000) {
        a2 &= ~0x10000;
        Sg2SepSetParam(ret, 0x200, 1, 0);
    }
    p->vab = vab;
    seseq = vab_get_seseq(vab, a1, a2);
    p->seseq = seseq;
    if (seseq == 0) {
        ret = -1;
        goto done;
    }
    mod = Sg2ModOpenSe(vab, a4);
    if (mod == -1) {
        ret = -2;
        goto done;
    }
    p->mod = mod;
    p->d28 = 0;
    p->d30 = 0;
    p->unk3C = p->seseq;
    p->d20 = 480.0 / (double)Sg2CtrlGetTickMode();
    p->unk38 = 0;
    p->status = 1;
    p->unk18 = a2;
    p->saved = 0;
    p->unk14 = a1;
    if (a3 != 0) {
        func_025B18(vab, a1, a2, a3);
    }
done:
    if (intr != 0) {
        EIntr();
    }
    return ret;
}
