/* STATUS (Session 9, 2026-10-15): NON_MATCHING. best score 22 [cc=296].
 * session9 R1; residual class not auto-classified
 * The original .s stays in the build (asm/cod/024F48.s); this C
 * draft (Session 9) is kept for the record. */
extern char __EH_FRAME_BEGIN__[];
extern char D_00169F70[];
extern int __CTOR_LIST__[];        /* table of function pointers */

int  __register_frame_info(int key, void *node);
int  func_00127460(void (*fn)(void));
void __do_global_dtors(void);

int __do_global_ctors(void) {
    int n;
    int i;

    __register_frame_info((int)__EH_FRAME_BEGIN__, D_00169F70);
    n = __CTOR_LIST__[0];
    if (n == -1) {
        n = 0;
        if (__CTOR_LIST__[1] != 0) {
            while (__CTOR_LIST__[n + 2] != 0)
                n++;
        }
    }
    if (n != 0) {
        for (i = n; i > 0; i--)
            ((void (*)(void))__CTOR_LIST__[i])();
    }
    return func_00127460(__do_global_dtors);
}
