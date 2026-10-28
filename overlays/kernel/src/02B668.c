/* KERNEL.XFF @ 0x02B668 (196 B) - Sg2SlotTbl
 * Evidence: debug table of the 24 Sg2 slots of a core (0xE0-byte records at .bss+0x97E30): one character per slot ('0' + vab at +4, '-' when 0), a space after every fourth slot except slot 0 and 24, NUL-terminated. UNCONFIRMED: names.
 */
struct Sg2Slot {
    unsigned int flags;
    int vab;
    char pad8[0xE0 - 8];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];

void Sg2SlotTbl(int core, char *out) {
    int i;
    int n = 0;
    char c;

    for (i = core * 24; i < core * 24 + 24; i++) {
        c = '-';
        if (D_kernel_bss_97E30[i].vab != 0) {
            c = D_kernel_bss_97E30[i].vab + '0';
        }
        out[n++] = c;
        if (i != 0 && i != 24 && i % 4 == 3) {
            out[n++] = ' ';
        }
    }
    out[n] = 0;
}
