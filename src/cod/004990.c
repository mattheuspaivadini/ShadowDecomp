/* asm/cod/004990.s -> LoaderSysInitTCP.
 * LoaderSysInitTCP; ldnet init, retry via goto, func_00104668 nothrow (defined earlier in the TU) (Session 35)
 * MATCHED. */
#include "nothrow_stub.h"
extern int D_0013A0EC;
extern char D_0013D000[];
extern char myaddr[];
extern char D_00137258[];   /* "reg_handler() failed.\n" */
extern char D_00137270[];   /* "cdrom0:\\MODULES2\\MCMAN.IRX;1" */
extern char D_00137290[];   /* "cdrom0:\\MODULES2\\MCSERV.IRX;1" */
extern char D_001372B0[];   /* "\n\tInitialize network environment " */
extern char D_001372D8[];   /* "failed.\n" */
extern char D_001372E8[];   /* "\t\tRetry by hdd ether " */
extern char D_00137300[];   /* "\tCheck your hardware environment...\n" */
extern char D_00137328[];   /* "ldnet: invalid addr\n" */
extern char D_00137340[];   /* "ldnet: my address: \"%s\"\n" */
extern char D_00137360[];   /* "ldnet: my address: \"%s\"[%s]\n" */
extern char D_00137380[];
extern char D_001373B8[];   /* "\t\t\tWelcome to " */
extern char D_001373C8[];   /* "\t\t\t     this ps2's ip address is " */
extern char D_0013A0F0[];
extern char D_0013A0F8[];   /* "mcserv" */
extern char D_0013A100[];   /* "mcman" */
extern char D_0013A108[];
extern char D_0013A110[];
int func_00104818(void);
void func_00104090(int mode);
int NOTHROW_STUB func_00104668(int a, int mode) { return 0; }
void sceSifMInitRpc(int mode);
int sceLibnetInitialize(void *cl, int a, int b, int c);
int sceLibnetRegisterHandler(void *cl, void *buf);
int sceInetAddress2String(void *cl, void *buf, char *name, int len, void *addr);
int sceInetAddress2Name(void *cl, void *buf, int flags, char *name, int len, void *addr, int ms, int nretry);
int func_001285C0(const char *fmt, ...);
int LoaderSysLoadIopModule(const char *path, int argc, const char *argp);
int LoaderSysUnloadIopModuleByName(const char *name, int a, int b, int c);
void PutString(int color, const char *fmt, ...);
void PutStringS(int color, const char *fmt, ...);

char *LoaderSysInitTCP(void)
{
    char name[0x80];
    char addr[0x80];
    int mode;

    if (D_0013A0EC)
        return D_0013D000;
    mode = func_00104818();
    func_00104090(mode);
    sceSifMInitRpc(0);
    sceLibnetInitialize(D_0013D000, 0x800, 0x2000, 0x20);
    if (sceLibnetRegisterHandler(D_0013D000, D_0013D000 + 0x40) < 0) {
        func_001285C0(D_00137258);
        while (1)
            ;
    }
    LoaderSysLoadIopModule(D_00137270, 0, 0);
    LoaderSysLoadIopModule(D_00137290, 0, 0);
    PutString(0xFFFFFF00, D_001372B0);
    if (mode == 0) {
        if (func_00104668(1, 0) != 0)
            goto done;
        PutStringS(0xFF804000, D_001372D8);
        PutString(0xFFFFFF00, D_001372E8);
        mode = 3;
    }
    if (func_00104668(0, mode) == 0) {
        PutStringS(0xFF804000, D_001372D8);
        PutString(0xFFFFFF00, D_00137300);
    }
done:
    if (sceInetAddress2String(D_0013D000, D_0013D000 + 0x40, addr, 0x80, myaddr)) {
        func_001285C0(D_00137328);
        while (1)
            ;
    }
    if (sceInetAddress2Name(D_0013D000, D_0013D000 + 0x40, 0, name, 0x80, myaddr, 0, 0)) {
        name[0] = 0;
        func_001285C0(D_00137340, addr);
    } else
        func_001285C0(D_00137360, name, addr);
    PutString(0xFFFFFF00, D_0013A0F0);
    LoaderSysUnloadIopModuleByName(D_0013A0F8, 0, 0, 0);
    LoaderSysUnloadIopModuleByName(D_0013A100, 0, 0, 0);
    PutString(0xFFFFFF00, D_0013A108);
    PutString(0xFFFF00, D_00137380);
    if (name[0]) {
        PutString(0xFFFF00, D_001373B8);
        PutString(0x40FF8000, D_0013A110, name);
    }
    PutString(0xFFFF00, D_001373C8);
    PutString(0x40FF8000, D_0013A110, addr);
    PutString(0xFFFF00, D_00137380);
    PutStringS(0xFFFF00, D_0013A108);
    D_0013A0EC = 1;
    return D_0013D000;
}
