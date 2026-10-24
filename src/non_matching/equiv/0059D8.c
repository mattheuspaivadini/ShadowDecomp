/* C equivalent of func_001059D8 (0059D8, 496 B @ 0x001059D8).
 *
 * Reconstructed instruction-by-instruction from asm/cod/0059D8.s and the
 * REA/Ghidra Emotion Engine dossier ev_cfa1d5f02063eb152123a1c99c405db4c5218c223d47c879ef644bb4aa95652b.
 * Readable reconstruction: NOT byte-exact (51 diff instructions in the
 * per-row scan and the PutFont argument setup), not part of the build.  The
 * codegen-tuned near-miss is src/non_matching/0059D8.c.
 *
 * Debug-console renderer over the 40x60 character screen at D_0013ED90:
 * for every row it trims trailing blanks, tracks the longest used row
 * (maxlen), renders the visible window starting at the scroll offset
 * D_0013A168, and finally clamps that offset so the window fits.
 *
 * Behaviour derived from the target:
 *   5A30  y*60 GIV, 5A4C y*15<<2  -> index arithmetic on the 8-byte Cell
 *   5A50  a0 = 0x20, 5A60  lbu    -> compare the cell char with ' '
 *   5A44  bnel + addiu a1          -> the scan runs right-to-left (do/while)
 *   5A90  slti/sltu                -> i >= 60 selects the scrolled window
 *   5AC0  daddu s3,s7              -> per-row copy of y*10 for PutFont
 *   5AE4  lw + sra/andi/srl        -> ARGB bytes, scaled by D_00139D80 (0.8f)
 *   5B7C  subu/slt -> conditional  -> the trailing scroll clamp
 */
struct console_cell {
    volatile int color;             /* 0x00: 0xARGB */
    char c;                         /* 0x04 */
    char pad[3];
};

extern struct console_cell D_0013ED90[40 * 60];   /* 40 rows x 60 columns */
extern int D_0013A168;              /* first visible column (scroll offset) */
extern int D_0013A150;              /* text colour, red   (0..255 * scale) */
extern int D_0013A154;              /* text colour, green */
extern int D_0013A158;              /* text colour, blue  */
extern float D_00139D80;            /* font scale, 0.8f in the image */

void PutFont(int c, int x, int y);

void func_001059D8(void)
{
    int y, x, i, maxlen, start;
    struct console_cell *p;
    float scale;
    int col;

    maxlen = 60;
    for (y = 0; y < 40; y++) {
        /* trim trailing blanks: i ends at the number of used columns */
        i = 59;
        do {
            if (D_0013ED90[y * 60 + i].c != ' ')
                break;
            i--;
        } while (i >= 0);
        i++;
        if (maxlen < i)
            maxlen = i;

        /* horizontal window: a full row scrolls by D_0013A168 */
        start = 0;
        if (i >= 60) {
            start = i - 60;
            if (i - D_0013A168 - 60 >= 0)
                start = D_0013A168;
        }

        p = &D_0013ED90[y * 60 + start];
        scale = D_00139D80;
        for (x = 0; x < 60; x++, p++) {
            if (p->c == ' ')
                continue;
            col = p->color;
            D_0013A154 = ((col >> 16) & 0xFF) * scale;
            D_0013A150 = ((col >> 24) & 0xFF) * scale;
            D_0013A158 = ((col >> 8) & 0xFF) * scale;
            PutFont(p->c, x * 10 - 300, y * 10 - 200);
        }
    }
    if (maxlen - D_0013A168 - 60 < 0)
        D_0013A168 = maxlen - 60;
}
