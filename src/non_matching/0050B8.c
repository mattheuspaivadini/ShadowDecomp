/* STATUS (Session 23, 2026-10-18): NON_MATCHING. best score 7 [cc=296] (was 25).
 * Typed rewrite (strcpy/struct chunk copy, pointer newline loop, sceSifCallRpc with the 9th stack arg). Residual = the gp-relative address of the sema id is hoisted out of the loop into $fp (one extra saved register); the original keeps lw %gp_rel(D+8) inside the loop. Same LICM class as 006498; -G16/-G32, volatile, -fno-rerun-loop-opt/-fno-gcse: no fix.
 * The original .s stays in the build (asm/cod/0050B8.s); this C
 * draft (Session 23) is kept for the record. */
struct S40 { char b[0x40]; };
struct SifRpcClientData { char pad00[0x24]; void *server; char pad28[0x10]; };
struct UsbSys { int f00; int f04; };
extern struct UsbSys D_0013A180;   /* small-data object; the sema id lives at +8 */
extern int D_0013EB00[0x40];
extern int D_0013EB40[8];
extern struct SifRpcClientData D_0013EAC0;
int sceSifCallRpc(struct SifRpcClientData *cd, int fno, int mode, void *send, int ssize,
                  void *recv, int rsize, void (*end)(void *), void *ea);
int func_001290C4(const char *s);           /* strlen */
char *func_00128FB0(char *d, const char *s); /* strcpy */
int WaitSema(int sema);
void func_001053F0(void *arg);

int usbSerialSysPutString(char *s) {
    int len;
    int n;
    int i;
    int r;
    char *buf;

    len = func_001290C4(s);
    while (len > 0) {
        if (len < 0x40) {
            func_00128FB0((char *)D_0013EB00, s);
            D_0013EB00[0x3F] = 0;
            n = len;
        } else {
            n = 0x40;
            *(struct S40 *)D_0013EB00 = *(struct S40 *)s;
        }
        for (i = 0, buf = (char *)D_0013EB00; i < n; i++, buf++)
            if (*buf == 0xA)
                *buf = 0xD;
        WaitSema(((int *)&D_0013A180)[2]);
        r = sceSifCallRpc(&D_0013EAC0, 0x10, 0, D_0013EB00, 0x40, D_0013EB40, 0x20, func_001053F0, 0);
        if (r != 0)
            return r;
        len -= n;
        s += n;
    }
    return D_0013EB40[0];
}
