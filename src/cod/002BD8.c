/* asm/cod/002BD8.s -> LoaderSysDeleteAllExternalThreadExceptMe.
 * LoaderSysDeleteAllExternalThreadExceptMe: matching
 * MATCHED (Session 12). */
extern int D_0013B790[];

int  GetThreadId(void);
void TerminateThread(int a0);
void DeleteThread(int a0);

void LoaderSysDeleteAllExternalThreadExceptMe(void) {
    int  value = -1;
    int  i;
    int  r;
    int *p;

    r = GetThreadId();
    for (i = 0xFF, p = D_0013B790; i >= 0; i--, p++) {
        if (*p == r)
            continue;
        if (*p < 0)
            continue;
        TerminateThread(*p);
        DeleteThread(*p);
        *p = value;
    }
}
