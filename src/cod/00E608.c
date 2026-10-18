/* asm/cod/00E608.s -> sceSifStopModule.
 * sceSifStopModule; twin of 00E400 with RPC fno 7 (Session 23)
 * MATCHED. */
struct Blob { char b[0xFC]; };
struct ModReq { int id; int arglen; char pad08[0xFC]; struct Blob args; char pad200[0x100 - 0xFC]; };
extern struct ModReq D_00147380;
extern char D_00147580[];
int func_0010E238(void);
int func_0010E338(void);
int sceSifCallRpc(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void *end, void *ea);
void *func_0012821C(void *dst, const void *src, int n);   /* memcpy */

int sceSifStopModule(int id, int arglen, const char *args, int *result) {
    if (func_0010E238() < 0)
        return 0xFFFF0000;
    if (func_0010E338() != 0)
        return 0xFFFEFFFC;
    D_00147380.id = id;
    if (args != 0) {
        if (arglen > 0xFC) {
            D_00147380.args = *(struct Blob *)args;
            D_00147380.arglen = 0xFC;
        } else {
            func_0012821C(&D_00147380.args, args, arglen);
            D_00147380.arglen = arglen;
        }
    } else
        D_00147380.arglen = 0;
    if (sceSifCallRpc(D_00147580, 7, 0, &D_00147380, 0x200, &D_00147380, 8, 0, 0) < 0)
        return 0xFFFEFFFF;
    {
        int r = D_00147380.id;
        *result = D_00147380.arglen;
        return r;
    }
}
