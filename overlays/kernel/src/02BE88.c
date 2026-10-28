/* KERNEL.XFF @ 0x02be88 (124 B) - Sg2SmfpPause
 * Evidence: the guard `bltz a0` returns 0; the 8 SMF records are 0x80 bytes at
 * .bss+0x9A880, `lw 8(rec)` is the module handle passed to Sg2ModSetParam and
 * `sw v1,0(rec)` the new state.  The image computes `&smf[i]` separately in both
 * arms (two HI16/LO16 pairs at +0x1c/+0x20 and +0x44/+0x48 => the loads use the
 * address value live across the call), then shares one tail store
 * (`sw v1,0(s0)`, v1 = 3 / 4 loaded in each arm after the call).  The two arms
 * differ only in the parameter id (0x20 pause / 0x40 continue) and the state
 * (3 / 4).  `if (i >= 0)` + a single `return 0` reproduces the epilogue
 * (`ld s0; daddu v0,zero,zero; ld ra`); the `i < 0` exit branches to `ld s0`.
 * The register file is pinned because the shipped code keeps the record pointer
 * in $16 (s0) and the state in $3 (v1); without the two `register ... asm`
 * locals the allocator picks $2/$3 the other way round (3 words differ).
 * UNCONFIRMED: field names (state/mod), the 0x9A880 table type and the
 * Sg2ModSetParam prototype.
 */
struct Sg2Smfp {
    int state;
    int unk4;
    int mod;
    char pad[0x80 - 0xC];
};
extern struct Sg2Smfp D_kernel_bss_9A880[];
void Sg2ModSetParam(int voice, int id, int val, int unk);

int Sg2SmfpPause(int i, int on) {
    register struct Sg2Smfp *p asm("$16");
    register int v asm("$3");

    if (i >= 0) {
        if (on) {
            p = &D_kernel_bss_9A880[i];
            Sg2ModSetParam(p->mod, 0x20, 1, 0);
            v = 3;
        } else {
            p = &D_kernel_bss_9A880[i];
            Sg2ModSetParam(p->mod, 0x40, 1, 0);
            v = 4;
        }
        p->state = v;
    }
    return 0;
}
