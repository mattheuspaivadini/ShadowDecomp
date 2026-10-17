/* asm/cod/004EF8.s -> padSysVibSetAcrParam.
 * padSysVibSetAcrParam (cc=296; sceVibSetActParam takes 5 args)
 * MATCHED. */
int sceVibSetActParam(int a0, int a1, void *a2, int a3, void *a4);

int padSysVibSetAcrParam(int a0, unsigned char *a1) {
    unsigned char data[2];
    unsigned char info;

    info = 3;
    data[0] = (unsigned char)((a1[0] & 1) | ((a1[1] & 0x7F) << 1));
    data[1] = (unsigned char)((a1[1] & 0x80) >> 7);
    return sceVibSetActParam(*(int *)(a0 + 0x11C), 1, &info, 2, data);
}
