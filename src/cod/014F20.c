/* func_00114F20 @ 0x00114F20 (0x34 bytes): if (a2 == 1) return
 * (unsigned)p->field10 < (unsigned)a1; else func_00114830(p, a1, a3),
 * return 0. */
int func_00114830(int *p, int a1, int a2);

int sceDmaWatch(int *p, int a1, int a2, int a3) {
    if (a2 == 1)
        return (unsigned)p[4] < (unsigned)a1;
    func_00114830(p, a1, a3);
    return 0;
}
