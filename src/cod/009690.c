/* func_00109690 @ 0x00109690 (0x40 bytes): same as 0093C8 but fields
 * forced to 0. */
int func_00112E40(int cmd, void *p, int size, int a, int b, int c);

int func_00109690(int a0, int a1, int a2, char *p) {
    int r = func_00112E40(0x80000008, p, 0x40, 0, 0, 0);

    if (r != 0)
        return 0;
    return 0x800;
}
