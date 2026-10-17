/* asm/cod/011700.s -> _InitAlarm.
 * counter init loop; -G0
 * MATCHED. */
struct alarm {
    struct alarm *next;
    int f04;
    int f08;
    int f0C;
};

extern struct alarm D_0014A880[64];
extern struct alarm *D_0014AC80;

int _InitAlarm(void) {
    struct alarm *p, *q;
    int i;

    D_0014AC80 = D_0014A880;
    p = &D_0014A880[63];
    q = &D_0014A880[64];
    for (i = 63; i >= 0; i--) {
        p->next = q;
        p--;
        q--;
    }
    D_0014A880[63].next = 0;
    return 0;
}
