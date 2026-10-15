/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 25 [cc=29].
 * R4 w25a_2: loop-entry b + hoisted i=0/p=buf
 * The original .s stays in the build (asm/cod/014108.s); this C
 * draft (Session 8) is kept for the record. */
extern char D_001384A8[];

int  sceStdioOpen(int a0, int a1, int a2);
int  sceStdioRead(int a0, int a1, int a2);
int  sceStdioClose(int a0);
int  func_00127500(int a0);

int func_00114108(void) {
    char buf[0x100];
    char *p;
    int fd;
    int i;

    fd = sceStdioOpen(D_001384A8, 1);
    if (fd < 0)
        return -1;
    i = 0;
    p = buf;
    while (i < 0x100) {
        sceStdioRead(fd, p, 1);
        if (*p == 0)
            break;
        i++;
        p++;
    }
    sceStdioClose(fd);
    return 0x1315670 < func_00127500(&buf[i - 9]);
}
