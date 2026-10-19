/* STATUS (Session 35, 2026-10-19): NON_MATCHING. best score 110 [cc=296].
 * console renderer over the 40x60 cell screen (1D index y*60+x, signed color bytes, scale copied
 * per row, PutFont per non-space cell). Residual = the trailing-space scan loop shape (original:
 * test char, i-- in the bne slot, bgez back) and the caller-saved a4/a5 constants spilled with sq.
 * Tried: for/while/do forms of the scan, 2D array, unsigned color.
 * The original .s stays in the build (asm/cod/0059D8.s); this C
 * draft (Session 35) is kept for the record. */
struct Cell { int color; char c; char pad[3]; };
extern struct Cell D_0013ED90[40 * 60];
extern int D_0013A168;
extern float D_00139D80;
extern int D_0013A150;
extern int D_0013A154;
extern int D_0013A158;
void PutFont(int c, int x, int y);

void func_001059D8(void)
{
    int y, x, i, maxlen, start;
    struct Cell *p;
    float scale;

    maxlen = 60;
    for (y = 0; y < 40; y++) {
        i = 59;
        while (i >= 0 && D_0013ED90[y * 60 + i].c == ' ')
            i--;
        i++;
        if (maxlen < i)
            maxlen = i;
        start = 0;
        if (i >= 60) {
            start = i - 60;
            if (i - D_0013A168 - 60 >= 0)
                start = D_0013A168;
        }
        p = &D_0013ED90[y * 60 + start];
        scale = D_00139D80;
        for (x = 0; x < 60; x++, p++) {
            if (p->c != ' ') {
                D_0013A154 = ((p->color >> 16) & 0xff) * scale;
                D_0013A150 = ((p->color >> 24) & 0xff) * scale;
                D_0013A158 = ((p->color >> 8) & 0xff) * scale;
                PutFont(p->c, x * 10 - 300, y * 10 - 200);
            }
        }
    }
    if (maxlen - D_0013A168 - 60 < 0)
        D_0013A168 = maxlen - 60;
}
