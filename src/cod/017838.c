/* asm/cod/017838.s -> func_00109B80.
 * drain loop + post-body guard; wave3d (R1)
 * MATCHED (Session 8). */
int func_00109B80(int *a);
int func_00108EF8(const char *msg);
void func_00107A08(int a0);

extern int D_00133A50[];    /* lui/%lo (non-small) */
extern char D_001389B0[];   /* lui/%lo */
extern char D_001355C0[];   /* lui/%lo, passed as the func_00109B80 argument */

int func_00117838(int a0) {
    if (a0 == 0) {
        if (D_00133A50[0] > 0)
            func_00108EF8(D_001389B0);
        while (func_00109B80((int *)D_001355C0) != 0)
            func_00107A08(0xFA0);
        return 0;
    }
    return func_00109B80((int *)D_001355C0);
}
