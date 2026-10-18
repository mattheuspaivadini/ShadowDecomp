/* asm/cod/009408.s -> func_00109408.
 * SIF cmd request forward; typed packet structs (void * fields 0x14/0x1C breaks TBAA dep), void tail-callee for the 2.9 tail j (Session 22)
 * MATCHED. */
struct Pk09 {
    int f00;
    int f04;
    int f08;
    int f0C;
    unsigned int f10;
    void * f14;
    int f18;
    void * f1C;
    int f20;
    int f24;
    int f28;
};
struct Rq09 {
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
    int f28;
    int f2C;
};

struct Rq09 *func_00109288(int a0);
struct Rq09 *func_001092B8(int a0, int a1);
int isceSifSendCmd(int cmd, void *p, int size, int a, int b, int c);
void iSetTimerAlarm(int a0, void (*a1)(), void *a2);
void func_001093C8();

int func_00109408(struct Pk09 *p, int a1) {
    struct Rq09 *q;
    int r;

    if (p->f10 & 4)
        q = func_001092B8(a1, p->f10 >> 16);
    else
        q = func_00109288(a1);
    q->f14 = p->f14;
    q->f1C = p->f1C;
    q->f20 = (int)0x8000000C;
    q->f24 = p->f20;
    q->f28 = p->f24;
    q->f2C = p->f28;
    r = isceSifSendCmd(0x80000008, q, 0x40, p->f20, p->f24, p->f28);
    if (r != 0)
        return r;
    iSetTimerAlarm(0x800, func_001093C8, q);
}
