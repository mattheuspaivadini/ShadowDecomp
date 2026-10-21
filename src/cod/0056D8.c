/* asm/cod/0056D8.s -> _putString.
 * console _putString; PutChar/ScrollDisplay inline, char-typed ternary join for the toupper store (Session 42)
 * MATCHED. */
struct Cell { int color; unsigned char c; char pad[3]; };
extern struct Cell D_0013ED90[40 * 60];
extern struct Cell D_0013A160;
extern int D_0013A16C;
extern int D_0013A170;
extern int D_0013A174;
extern int D_0013A178;
extern int D_0013A17C;
extern char _ctype_[];
int LoaderSysPrintf(const char *fmt, ...);
unsigned int func_001290C4(const char *s);   /* strlen */

/* Same bodies as PutChar (006B58) and ScrollDisplay (006390); the original expands them in place. */
static __inline__ void PutChar(int a0, unsigned char a1) {
    int idx = D_0013A170 * 60 + D_0013A16C;

    D_0013ED90[idx].color = a0;
    D_0013ED90[idx].c = a1;
}

static __inline__ void ScrollDisplay(void) {
    int i;
    int j;

    for (i = 1; i < 0x28; i++)
        for (j = 0; j < 0x3C; j++)
            D_0013ED90[(i - 1) * 0x3C + j] = D_0013ED90[i * 0x3C + j];
    for (j = 0; j < 0x3C; j++)
        D_0013ED90[0x27 * 0x3C + j] = D_0013A160;
}

void _putString(int color, char *s)
{
    unsigned int i;
    int t;
    struct Cell *p;

    LoaderSysPrintf(s);
    for (i = 0; i < func_001290C4(s); i++) {
        if (s[i] == '\t') {
            PutChar(0xFFFFFF00, ' ');
            D_0013A16C += 2;
        } else if (s[i] == '\n') {
            PutChar(0xFFFFFF00, ' ');
            D_0013A170++;
            D_0013A16C = 0;
            D_0013A174 = 0;
        } else {
            p = &D_0013ED90[D_0013A170 * 60 + D_0013A16C];
            p->color = color;
            if (s[i] == '\'')
                D_0013A178 = !D_0013A178;
            if (s[i] == '"')
                D_0013A17C = !D_0013A17C;
            p->c = D_0013A17C != 0 ? s[i] : (char)(t = ((_ctype_ + 1)[(int)s[i]] & 2 ? s[i] - 0x20 : s[i]));
            D_0013A16C++;
        }
        if (D_0013A16C >= 60)
            D_0013A16C = 59;
        if (D_0013A170 >= 40) {
            ScrollDisplay();
            D_0013A170 = 39;
        }
    }
}
