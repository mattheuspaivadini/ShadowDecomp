/* KERNEL.XFF @ 0x022d50 (200 B) - Sg2ModGetParam
 * Evidence: three-way `switch` on the parameter id lowered as a decision tree
 * (test 4, then <5, then 1, then 8).  Case 1 stores the int at +0x34 (out1)
 * and +0x38 (out2); case 4 stores the int at +0x3C; case 8 stores +0x40.  The
 * record stride is 2480 B (i*5 -> <<5 -> -i*5 -> <<4) off .bss+0x7F6D8, so the
 * accessed fields are +0x30/+0x34/+0x38/+0x3C/+0x40 of a 2480-byte record (the
 * 0x30 add is emitted as `addiu v0,v0,0x30` before the base add).
 * UNCONFIRMED: record type/field names, the parameter numbering.
 * Flags: the delayed-branch scheduler must be on (-g0): the `return 0` value is
 * placed in the `jr ra` delay slot only then.
 */
struct Sg2Mod {
    char pad0[0x30];
    int f30;
    int f34;
    int f38;
    int f3C;
    int f40;
    char pad44[2480 - 0x44];
};
extern struct Sg2Mod D_kernel_bss_7F6D8[];

int Sg2ModGetParam(int id, int param, int *out1, int *out2) {
    switch (param) {
    case 1:
        *out1 = D_kernel_bss_7F6D8[id].f34;
        *out2 = D_kernel_bss_7F6D8[id].f38;
        break;
    case 4:
        *out1 = D_kernel_bss_7F6D8[id].f3C;
        break;
    case 8:
        *out1 = D_kernel_bss_7F6D8[id].f40;
        break;
    }
    return 0;
}
