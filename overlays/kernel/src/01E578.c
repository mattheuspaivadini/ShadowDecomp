/* KERNEL.XFF @ 0x01E578 (116 B) - sndVabCreate   [MATCH: -G0]
 * Evidence: scans the 20 0x1C-byte VAB records at .bss+0x7D1D8 for the first
 * one whose flags word (+0) has bit 0 clear; on a hit it sets the bit, stores
 * -1 at +4 and 0 at +0x10 and returns that record, otherwise it returns 0.
 * The image keeps three induction values alive (the load cursor $a3, the
 * record address $t1 = base + i*0x1C and the byte offset $a0 = i*0x1C), which
 * falls out of the `D[i]` subscript form, and the `nop` before the hit block
 * is the alignment pad of the `jr $ra` in the not-found path.
 * UNCONFIRMED: struct/field names, the `20` count semantics.
 * Lever: `for (i = 0; i < 20; i++) if (...) goto found;` + `return &D[i]` for
 * the hit block gives the rotated loop and the shared epilogue.
 */
struct Vab {
    unsigned int flags;
    int unk04;
    int unk08;
    int unk0C;
    int unk10;
    char pad14[0x1C - 0x14];
};
extern struct Vab D_kernel_bss_7D1D8[20];

struct Vab *sndVabCreate(void) {
    int i;

    for (i = 0; i < 20; i++) {
        if (!(D_kernel_bss_7D1D8[i].flags & 1))
            goto found;
    }
    return 0;
found:
    D_kernel_bss_7D1D8[i].flags |= 1;
    D_kernel_bss_7D1D8[i].unk04 = -1;
    D_kernel_bss_7D1D8[i].unk10 = 0;
    return &D_kernel_bss_7D1D8[i];
}
