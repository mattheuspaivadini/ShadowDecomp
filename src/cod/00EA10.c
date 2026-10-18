/* asm/cod/00EA10.s -> func_0010EA10.
 * module RPC request carrying a module path (strncpy to 0xFC, NUL-terminated) plus argument blob; twin of 00E400's request layout (Session 23)
 * MATCHED. */
struct Blob { char b[0xFC]; };
struct ModReq { int arglen; int result; char path[0xFC]; struct Blob args; char pad200[0x100 - 0xFC]; };
extern struct ModReq D_00147380;
extern char D_00147580[];
int func_0010E238(void);
int func_0010E338(void);
int sceSifCallRpc(void *cd, int fno, int mode, void *send, int ssize, void *recv, int rsize, void *end, void *ea);
void *func_0012821C(void *dst, const void *src, int n);   /* memcpy */
char *func_001293B8(char *dst, const char *src, int n);   /* strncpy */

int func_0010EA10(const char *path, int arglen, const char *args, int *result, int fno) {
    if (func_0010E238() < 0)
        return 0xFFFF0000;
    if (func_0010E338() != 0)
        return 0xFFFEFFFC;
    func_001293B8(D_00147380.path, path, 0xFC);
    D_00147380.path[0xFB] = 0;
    if (args != 0) {
        if (arglen > 0xFC) {
            D_00147380.args = *(struct Blob *)args;
            D_00147380.arglen = 0xFC;
        } else {
            func_0012821C(&D_00147380.args, args, arglen);
            D_00147380.arglen = arglen;
        }
    } else {
        D_00147380.args.b[0] = 0;
        D_00147380.arglen = 0;
    }
    if (sceSifCallRpc(D_00147580, fno, 0, &D_00147380, 0x200, &D_00147380, 8, 0, 0) < 0)
        return 0xFFFEFFFF;
    {
        int r = D_00147380.arglen;
        *result = D_00147380.result;
        return r;
    }
}
