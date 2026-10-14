/* STATUS (Session 7, 2026-10-14): NON_MATCHING. best score 3 [cc=296, default].
 * bit repack into a 2-byte block + 6-arg call; field-0 store order differs.
 * The original .s stays in the build (asm/cod/004EF8.s); this C
 * draft (subagent-produced, Session 7) is kept for the record. */
/* asm/cod/004EF8.s -> func_00104EF8 @ 0x00104EF8 (0x60 bytes, 24 insns)
 *
 * Repack the two-byte blob a1 and send it through func_00115940 (the DBC "send
 * two chunks" helper: (handle, len1, src1, len2, src2, extra)):
 *   data[0] = (a1[0] & 1) | ((a1[1] & 0x7F) << 1);
 *   data[1] = (a1[1] & 0x80) >> 7;
 *   info    = 3;
 *   func_00115940(*(int *)(a0 + 0x11C), 1, &info, 2, data, 3);
 * (the callee copies (a4, a3) = 2 bytes and (a2, a1) = 1 byte, so the 1-byte
 * chunk is the flag byte 3 and the 2-byte chunk is the repacked blob).
 *
 * Frame 0x30 with the 2-byte blob at 0x00, the flag byte at 0x10 and $ra at
 * 0x20 - a 16-byte slot per local, i.e. the 2.9 (cc=29) slot layout (with
 * cc=296 the flag byte would land at 0x02). $a5 = 3 (the 6th, unused argument)
 * is the same literal the flag byte gets; the emission order of the three
 * stores is data[1], data[0], info.
 * MATCH GUESS: cc=29 */
int func_00115940(int a0, int a1, void *a2, int a3, void *a4, int a5);

int func_00104EF8(int a0, unsigned char *a1) {
    unsigned char data[2];
    unsigned char info;

    info = 3;
    data[0] = (unsigned char)((a1[0] & 1) | ((a1[1] & 0x7F) << 1));
    data[1] = (unsigned char)((a1[1] & 0x80) >> 7);
    return func_00115940(*(int *)(a0 + 0x11C), 1, &info, 2, data, 3);
}
