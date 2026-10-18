/* asm/cod/0096D0.s -> func_001096D0.
 * SIF cmd reply forward; same typed packet structs as 009408 (Session 22)
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

struct Ent09 { int f00; int f04; int f08; };
struct Rq09 *func_00109288(int a0);
struct Ent09 *func_00109640(int key, int a1);
int isceSifSendCmd(int cmd, void *p, int size, int a, int b, int c);
void iSetTimerAlarm(int a0, void (*a1)(), void *a2);
void func_00109690();

int func_001096D0(struct Pk09 *p, int a1) {
    struct Rq09 *q;
    struct Ent09 *e;
    int r;

    q = func_00109288(a1);
    q->f14 = p->f14;
    q->f1C = p->f1C;
    q->f20 = (int)0x80000009;
    e = func_00109640(p->f20, a1);
    if (e == 0) {
        q->f24 = 0;
        q->f28 = 0;
    } else {
        q->f24 = (int)e;
        q->f28 = e->f08;
    }
    r = isceSifSendCmd(0x80000008, q, 0x40, 0, 0, 0);
    if (r != 0)
        return r;
    iSetTimerAlarm(0x800, func_00109690, q);
}
