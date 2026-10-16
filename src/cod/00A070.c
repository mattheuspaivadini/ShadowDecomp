/* asm/cod/00A070.s -> func_00109E50.
 * session9 step1 residue: nested drain-loop form
 * MATCHED (Session 8). */
int *sceSifGetNextRequest(int *ctx);
void sceSifExecRequest(int *node);
void SleepThread(void);

void sceSifRpcLoop(int *ctx) {
    int *node;
    int *c;

    c = ctx;
    for (;;) {
        while ((node = sceSifGetNextRequest(c)) != 0)
            sceSifExecRequest(node);
        SleepThread();
    }
}
