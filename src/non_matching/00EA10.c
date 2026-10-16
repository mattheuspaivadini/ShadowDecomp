/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 83 [cc=29].
 * R3 famD: strncpy via func_001293B8 + store order
 * The original .s stays in the build (asm/cod/00EA10.s); this C
 * draft (Session 8) is kept for the record. */
int func_0010E238(void);
int func_0010E338(void);
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
int func_0012821C(int dst, int src, int n);
int func_001293B8(int dst, int src, int n);   /* strncpy-like: NUL-fills */

extern int D_00147380[];   /* .bss request/payload, non-small -> lui/%lo */
extern int D_00147580[];   /* .bss transfer buffer      -> lui/addiu   */

struct B_EA10 {            /* the fixed 0xFC-byte blob at request + 0x104 */
    unsigned int w[0x3F];  /* 0xFC bytes */
};

int func_0010EA10(int a0, int a1, int a2, int *a3, int a4) {
    if (func_0010E238() < 0)
        return 0xFFFF0000;
    if (func_0010E338() != 0)
        return 0xFFFEFFFC;
    func_001293B8((int)D_00147380 + 8, a0, 0xFC);
    ((char *)D_00147380)[0x103] = 0;
    if (a2 == 0) {
        ((char *)D_00147380)[0x104] = 0;
        D_00147380[0] = 0;
    } else if (a1 < 0xFD) {
        func_0012821C((int)D_00147380 + 0x104, a2, a1);
        D_00147380[0] = a1;
    } else {
        *(struct B_EA10 *)((char *)D_00147380 + 0x104) = *(struct B_EA10 *)a2;
        D_00147380[0] = 0xFC;
    }
    if (sceSifCallRpc((int)D_00147580, a4, 0, (int)D_00147380, 0x200,
                      (int)D_00147380, 8, 0, 0) < 0)
        return 0xFFFEFFFF;
    *a3 = D_00147380[1];
    return D_00147380[0];
}
