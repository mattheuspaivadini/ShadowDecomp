/* asm/cod/022EA8.s -> func_00122EA8.
 * RPC command dispatcher (0xC/0xD/0xE); callback pointers in .data, arguments evaluated before the null check, unsigned command (Session 23)
 * MATCHED. */
struct Arg { int f00; int f04; int f08; int f0C; int f10; char buf[4]; };
extern int (*D_00169F04)(char *a, char *b, int c, int d, int *e) __attribute__((section(".data")));
extern int (*D_00169F08)(int a, char *b, char *c, int *d, int e, int f) __attribute__((section(".data")));
extern int (*D_00169F0C)(int a) __attribute__((section(".data")));

struct Arg *func_00122EA8(unsigned int cmd, struct Arg *p) {
    int r = -1;

    switch (cmd) {
    case 0xC: {
        int (*fn)(char *, char *, int, int, int *) = D_00169F04;
        char *a = (char *)&p->f10;
        char *b = (char *)&p->f10 + p->f08;
        int c = p->f00;
        int d = p->f04;
        if (fn)
            r = fn(a, b, c, d, &p->f04);
        break;
    }
    case 0xD: {
        int (*fn)(int, char *, char *, int *, int, int) = D_00169F08;
        int a = p->f00;
        char *b = p->buf;
        char *c = p->buf + p->f04;
        int e = p->f0C;
        int f = p->f10;
        if (fn)
            r = fn(a, b, c, &p->f04, e, f);
        break;
    }
    case 0xE: {
        int (*fn)(int) = D_00169F0C;
        int a = p->f00;
        if (fn)
            r = fn(a);
        break;
    }
    }
    p->f00 = r;
    return p;
}
