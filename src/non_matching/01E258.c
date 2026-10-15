/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 19 [cc=29].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/01E258.s); this C
 * draft (Session 9) is kept for the record. */
int func_00120CD0(int a0, char *a1, unsigned int a2, int a3);
int func_0011C4C8(int a0, unsigned int a1, unsigned int *a2);

extern char D_0015F080[];

int func_0011E258(int a0, int a1, int a2, unsigned int *a3) {
    int found = 0;
    int count = a2;
    unsigned int arg = (unsigned int)a1;
    int j;

    *a3 = 0;
    for (;;) {
        if (func_00120CD0(a0, D_0015F080, arg, 1) == 0) {
            *a3 = 0x8101006F;
            return -1;
        }
        j = 0;
        for (;;) {
            unsigned int w = ((unsigned short *)D_0015F080)[j * 0x100];

            if ((w & 0x8000) == 0)
                found++;
            if (--count == 0)
                return j == 0 ? found + 1 : found;
            if (++j >= 2)
                break;
        }
        arg = (unsigned int)func_0011C4C8(a0, arg, a3);
        if (*a3 != 0)
            return -1;
        if (arg == 0xFFFFFFFF)
            return found;
        arg = arg & 0x7FFFFFFF;
    }
}
