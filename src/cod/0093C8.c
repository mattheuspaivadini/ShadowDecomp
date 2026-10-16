/* func_001093C8 @ 0x001093C8 (0x40 bytes): forward fields 0x24/0x28/0x2C
 * of the 5th-argument struct pointer to func_00112E40(0x80000008, p, 0x40,
 * ...); 0 on success, 0x800 on failure. */
int isceSifSendCmd(int cmd, void *p, int size, int a, int b, int c);

int func_001093C8(int a0, int a1, int a2, char *p) {
    int r = isceSifSendCmd(0x80000008, p, 0x40,
                          *(int *)(p + 0x24), *(int *)(p + 0x28),
                          *(int *)(p + 0x2C));

    if (r != 0)
        return 0;
    return 0x800;
}
