/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 26 [cc=29].
 * R3 famC: 0x40-byte ldl/ldr struct copy + "+0x80" address form
 * The original .s stays in the build (asm/cod/016030.s); this C
 * draft (Session 8) is kept for the record. */
struct S40 {
    int w[16];              /* 0x00..0x3F */
};

extern int D_00150D00[];    /* .bss 0x00150D00, 0x80 bytes -> lui/%lo */
extern int D_00150D80[];    /* .bss 0x00150D80, 0x80 bytes -> lui/%lo */
extern int D_00150DC0[];    /* .bss 0x00150DC0 (the lock handle) -> lui/%lo */
extern int D_0014E900[];    /* .bss 0x0014E900 (request) -> lui/%lo */
extern int D_0014EA00[];    /* .bss 0x0014EA00, 0xC0 bytes -> lui/%lo */
extern char D_001386C0[];   /* .rodata: the error message -> lui/%lo */

int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);
void SyncDCache(int a0, int a1);
void DIntr(void);
void EIntr(void);
void WaitSema(int a0);
void SignalSema(int a0);
void func_00116C58(int a0);

int sceDbcGetDepNumber(int a0) {
    int r;
    int v;

    SyncDCache((int)D_00150D00, (int)D_00150D00 + 0x80);
    DIntr();
    *(struct S40 *)D_00150D80 = *(struct S40 *)D_00150D00;
    EIntr();
    if (D_00150D80[a0] != 1)
        return -0xC;
    WaitSema(D_00150DC0[0]);
    D_0014EA00[0] = a0;
    r = sceSifCallRpc((int)D_0014E900, 0x80001303, 0, (int)D_0014EA00, 0x90,
                      (int)D_0014EA00, 0x90, 0, 0);
    if (r < 0) {
        func_00116C58((int)D_001386C0);
        SignalSema(D_00150DC0[0]);
        return 0;
    }
    v = D_0014EA00[1];
    SignalSema(D_00150DC0[0]);
    return v;
}
