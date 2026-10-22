/* asm/cod/004428.s -> load_set_conf_only.
 * load_set_conf_only; netcnfif sequence with an inline wait_result helper, second result kept in r (Session 35)
 * MATCHED. */
typedef struct {
    int data;
    int f_no_decode;
    int type;
    int addr;
    char pad[0x300];
} sceNetcnfifArg_t;

extern char D_00137008[];   /* "ldnet: network resource info: \"%s\"\n" */
extern char D_00136FB8[];   /* "cdrom0:\\MODULES2\\NETCNFIF.IRX;1" */
extern char D_00136FD8[];   /* "NETCNFIF" */
int func_001285C0(const char *fmt, ...);
int LoaderSysLoadIopModule(const char *path, int argc, const char *argp);
void setNewIopIdentifier(const char *name);
int FlushCache(int mode);
void sceNetcnfifSetup(void);
void sceNetcnfifAllocWorkarea(int size);
int sceNetcnfifCheck(void);
void sceNetcnfifGetResult(sceNetcnfifArg_t *result);
void sceNetcnfifSetFNoDecode(int f_no_decode);
void sceNetcnfifLoadEntry(char *fname, int type, char *usr_name, void *data);
void sceNetcnfifGetAddr(void);
int sceNetcnfifSendIOP(void *data, int addr, int size);
int sceNetcnfifDmaCheck(int id);
void sceNetcnfifSetEnv(int type);
int sceInetCtlSetAutoMode(int a, int b, int f);
int sceLibnetSetConfiguration(int a, int b, int addr);

static __inline__ int wait_result(sceNetcnfifArg_t *arg)
{
    while (sceNetcnfifCheck())
        ;
    sceNetcnfifGetResult(arg);
    return arg->data;
}

int load_set_conf_only(int a, int b, void *data, char *fname, char *usr_name, int flags)
{
    sceNetcnfifArg_t if_arg;
    int id, addr, r;

    func_001285C0(D_00137008, fname);
    if (flags & 4) {
        if (LoaderSysLoadIopModule(D_00136FB8, 0, 0) < 0)
            return -1;
        setNewIopIdentifier(D_00136FD8);
    }
    sceNetcnfifSetup();
    sceNetcnfifAllocWorkarea(0x1000);
    if (wait_result(&if_arg) < 0)
        return -540;
    if (flags & 1)
        sceNetcnfifSetFNoDecode(0);
    else
        sceNetcnfifSetFNoDecode(1);
    FlushCache(0);
    sceNetcnfifLoadEntry(fname, 0, usr_name, data);
    r = wait_result(&if_arg);
    if (r < 0)
        return -540;
    sceNetcnfifGetAddr();
    if (wait_result(&if_arg) < 0)
        return -540;
    id = sceNetcnfifSendIOP(data, if_arg.addr, 0x1340);
    if (id == 0)
        return -540;
    while (sceNetcnfifDmaCheck(id))
        ;
    sceNetcnfifSetEnv(0);
    if (wait_result(&if_arg) < 0)
        return -540;
    addr = if_arg.addr;
    if (flags & 2)
        r = sceInetCtlSetAutoMode(a, b, 1);
    else
        r = sceInetCtlSetAutoMode(a, b, 0);
    if (r < 0)
        return r;
    r = sceLibnetSetConfiguration(a, b, addr);
    if (r < 0)
        return r;
    return 0;
}
