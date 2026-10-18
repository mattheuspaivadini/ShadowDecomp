/* asm/cod/011F18.s -> read.
 * read(); tty fd 0, sceTtyInit takes no argument (Session 23)
 * MATCHED. */
extern int D_00133940 __attribute__((section(".data")));
int sceTtyInit(void);
int sceTtyRead(void *buf, int n);

int read(int fd, void *buf, int n) {
    if (fd == 0) {
        if (D_00133940 == 0) {
            if (sceTtyInit() == 0) return -1;
            D_00133940 = 1;
        }
        return sceTtyRead(buf, n);
    }
    return -1;
}
