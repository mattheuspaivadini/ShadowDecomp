/* asm/cod/014108.s -> func_00114108.
 * ROMVER date check; unsigned index, *p++ test (Session 23)
 * MATCHED. */
extern char D_001384A8[];
int sceOpen(const char *name, int mode);
int sceRead(int fd, void *buf, int n);
int sceClose(int fd);
int atoi(const char *s);

int func_00114108(void) {
    char buf[0x100];
    char *p;
    unsigned int i;
    int fd;
    fd = sceOpen(D_001384A8, 1);
    if (fd < 0) return -1;
    for (i = 0, p = buf; i < sizeof(buf); i++) {
        sceRead(fd, p, 1);
        if (*p++ == 0) break;
    }
    sceClose(fd);
    if (atoi(&buf[i - 9]) > 0x1315670) return 1;
    return 0;
}
