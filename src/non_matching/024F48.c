/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 22 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/024F48.s); this C
 * draft (Session 9) is kept for the record. */
extern char D_001360E0[];
extern char D_00169F70[];
extern int D_001360CC[];        /* table of function pointers */

int  func_001260A8(int key, void *node);
int  func_00127460(void (*fn)(void));
void func_00124EB8(void);

int func_00124F48(void) {
    int n;
    int i;

    func_001260A8((int)D_001360E0, D_00169F70);
    n = D_001360CC[0];
    if (n == -1) {
        n = 0;
        if (D_001360CC[1] != 0) {
            while (D_001360CC[n + 2] != 0)
                n++;
        }
    }
    if (n != 0) {
        for (i = n; i > 0; i--)
            ((void (*)(void))D_001360CC[i])();
    }
    return func_00127460(func_00124EB8);
}
