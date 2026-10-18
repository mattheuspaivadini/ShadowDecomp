/* asm/cod/0050B8.s -> usbSerialSysPutString.
 * The semaphore id is its own 4-byte .sbss object D_0013A188 (split out of D_0013A180 in 4b19c67): a plain small-data global keeps the gp-relative load inside the loop instead of hoisting gp+8 into a saved register (Session 26).
 * MATCHED. */
struct S40 { char b[0x40]; };
struct SifRpcClientData { char pad00[0x24]; void *server; char pad28[0x10]; };
extern int D_0013A188;              /* sema id (.sbss) */
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
        WaitSema(D_0013A188);
        r = sceSifCallRpc(&D_0013EAC0, 0x10, 0, D_0013EB00, 0x40, D_0013EB40, 0x20, func_001053F0, 0);
        if (r != 0)
            return r;
        len -= n;
        s += n;
    }
    return D_0013EB40[0];
}
