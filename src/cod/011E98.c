/* asm/cod/011E98.s -> write.
 * write(); tty fd 1/2, sceTtyInit takes no argument (Session 23)
 * MATCHED. */
extern int D_00133940 __attribute__((section(".data")));
int sceTtyInit(void);
int sceTtyWrite(const void *buf, int n);

int write(int fd, const void *buf, int n) {
    if (fd == 1 || fd == 2) {
        if (D_00133940 == 0) {
            if (sceTtyInit() == 0) return -1;
            D_00133940 = 1;
        }
        return sceTtyWrite(buf, n);
    }
    return -1;
}
