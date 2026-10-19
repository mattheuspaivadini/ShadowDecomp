/* asm/cod/01B458.s -> func_0011B458.
 * libmc2 server thread: wait for a command, switch dispatch to the _sceMcFat* calls (case order follows the code layout, 16..24 are empty), remap 0x81019FFF, signal completion (Session 34)
 * MATCHED. */
struct H { int thid; int sema0; int sema1; };

struct McCmd {
    int port;                   /* 0x000 */
    int cmd;                    /* 0x004 */
    int result;                 /* 0x008 */
    int a0C;                    /* 0x00C */
    int a10;                    /* 0x010 */
    int a14;                    /* 0x014 */
    int a18;                    /* 0x018 */
    char pad1C[0x41C - 0x1C];
    char name[0x80];            /* 0x41C */
    char name2[0x80];           /* 0x49C */
};

extern struct H D_00151E20;
extern struct McCmd D_00151900;

int WaitSema(int sid);
int SignalSema(int sid);
int _sceMcFatGetInfo(int port, int info);
int _sceMcFatReadFile(int port, char *name, int a, int b, int c);
int _sceMcFatWriteFile(int port, char *name, int a, int b, int c);
int _sceMcFatFormat(int port);
int _sceMcFatCreateFile(int port, char *name, int mode);
int _sceMcFatDeleteFile(int port, char *name);
int _sceMcFatChDir(int port, char *name, int a);
int _sceMcFatGetDir(int port, char *name, int a, int b, int c, int d);
int _sceMcFatSetAttr(int port, char *name, unsigned short attr);
int _sceMcFatRename(int port, char *name, char *name2);
int _sceMcFatUnFormat(int port);
int _sceMcFatSearchFile(int port, char *name, int a);
int _sceMcFatGetEntSpace(int port, char *name);

void func_0011B458(void *arg) {
    for (;;) {
        WaitSema(D_00151E20.sema0);
        switch (D_00151900.cmd) {
        case 2:
            D_00151900.result = _sceMcFatGetInfo(D_00151900.port, D_00151900.a0C);
            break;
        case 5:
            D_00151900.result = _sceMcFatReadFile(D_00151900.port, D_00151900.name, D_00151900.a0C, D_00151900.a10, D_00151900.a14);
            break;
        case 6:
            D_00151900.result = _sceMcFatWriteFile(D_00151900.port, D_00151900.name, D_00151900.a0C, D_00151900.a10, D_00151900.a14);
            break;
        case 3:
            D_00151900.result = _sceMcFatFormat(D_00151900.port);
            break;
        case 7:
            D_00151900.result = _sceMcFatCreateFile(D_00151900.port, D_00151900.name, D_00151900.a0C);
            break;
        case 8:
            D_00151900.result = _sceMcFatDeleteFile(D_00151900.port, D_00151900.name);
            break;
        case 11:
            D_00151900.result = _sceMcFatCreateFile(D_00151900.port, D_00151900.name, D_00151900.a0C);
            break;
        case 12:
            D_00151900.result = _sceMcFatChDir(D_00151900.port, D_00151900.name, D_00151900.a0C);
            break;
        case 10:
            D_00151900.result = _sceMcFatGetDir(D_00151900.port, D_00151900.name, D_00151900.a0C, D_00151900.a10, D_00151900.a14, D_00151900.a18);
            break;
        case 13:
            D_00151900.result = _sceMcFatSetAttr(D_00151900.port, D_00151900.name, D_00151900.a0C);
            break;
        case 9:
            D_00151900.result = _sceMcFatRename(D_00151900.port, D_00151900.name, D_00151900.name2);
            break;
        case 4:
            D_00151900.result = _sceMcFatUnFormat(D_00151900.port);
            break;
        case 14:
            D_00151900.result = _sceMcFatSearchFile(D_00151900.port, D_00151900.name, D_00151900.a0C);
            break;
        case 15:
            D_00151900.result = _sceMcFatGetEntSpace(D_00151900.port, D_00151900.name);
            break;
        case 16: case 17: case 18: case 19: case 20:
        case 21: case 22: case 23: case 24:
            break;
        }
        if (D_00151900.result == 0x81019FFF)
            D_00151900.result = 0x81010002;
        SignalSema(D_00151E20.sema1);
    }
}
