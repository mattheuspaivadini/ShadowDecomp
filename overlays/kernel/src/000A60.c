/* KERNEL.XFF @ 0x000A60 (60 B) - iosCreateSema
 * Evidence: 0x30 frame with a 0x18-byte SemaParam at $sp (initCount at +8 from
 * $a0, maxCount at +4 from $a1), `CreateSema(&p)`, the id kept in $s0 across
 * `LoaderSysEntryExternalSemaList(id)` and returned. SemaParam is the SCE
 * libkernel layout.
 */
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
int CreateSema(struct SemaParam *sema);
void LoaderSysEntryExternalSemaList(int sema);

int iosCreateSema(int init, int max) {
    struct SemaParam p;
    int sema;

    p.initCount = init;
    p.maxCount = max;
    sema = CreateSema(&p);
    LoaderSysEntryExternalSemaList(sema);
    return sema;
}
