/* asm/cod/00F4C0.s -> SetTLBEntry.
 * SetTLBEntry (SHN_ABS)
 * MATCHED (Session 12). */
int func_0010F4B0(int a0);

int SetTLBEntry(int a0) {
    int r = a0 - 0xD;

    if ((unsigned)r < 0x23)
        return func_0010F4B0(a0);
    return -1;
}
