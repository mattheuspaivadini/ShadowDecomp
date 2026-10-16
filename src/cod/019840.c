/* asm/cod/019840.s -> func_00118380.
 * session9 R1 w25b wave
 * MATCHED (Session 8). */
int func_00118380(int a0, int a1, int a2, int a3, int a4);

int sceLibnetWaitGetInterfaceEvent(int a0, int *a1, int *a2, int *a3) {
    int r;

    r = func_00118380(a0, 0x23, (int)a1, 0, 0xC);
    if (r < 0)
        return -0x21E;
    if (a2 != 0)
        *a2 = a1[1];
    if (a3 != 0)
        *a3 = a1[2];
    return a1[0];
}
