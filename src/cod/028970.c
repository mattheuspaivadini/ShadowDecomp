/* asm/cod/028970.s -> _kill_r.
 * _kill_r (SHN_ABS)
 * MATCHED (Session 12). */
extern int D_0013A180[];

int kill(int pid, int sig);

int _kill_r(int *ptr, int pid, int sig) {
    int ret;
    int *p = &D_0013A180[3];

    *p = 0;
    if ((ret = kill(pid, sig)) == -1 && *p != 0)
        *ptr = *p;
    return ret;
}
