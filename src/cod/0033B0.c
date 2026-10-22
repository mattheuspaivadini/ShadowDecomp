/* asm/cod/0033B0.s -> func_001033B0.
 * loader IOP bring-up; module-load and IOP-reboot helpers expanded inline, int-returning sceDmaReset (Session 35)
 * MATCHED. */
extern char D_00136B00[];   /* "\t\tLoading " */
extern char D_00136B10[];   /* "ERROR\n\t\t\tCouldn't load \"%s\".\n\t\t\t\t( Error code: %d )\n" */
extern char D_0013A018[];   /* "%s" */
extern char D_0013A020[];
extern char D_0013A028[];   /* "Done.\n" */
extern char D_00136B98[];   /* "Initialize loader (Version: " */
extern char D_0013A038[];
extern char D_00136BB8[];   /* __DATE__ */
extern char D_00136BC8[];   /* __TIME__ */
extern char D_0013A040[];
extern char D_00136BD8[];   /* "\tWarm up CD/DVD hardware... " */
extern char D_00136AE8[];   /* "\tRebooting Iop\n\t\twith " */
extern char D_00136BF8[];   /* "cdrom0:\\IOPRP300.IMG;1" */
extern char D_00136C10[];   /* SIO2MAN.IRX */
extern char D_00136C30[];   /* DBCMAN.IRX */
extern char D_00136C50[];   /* SIO2D.IRX */
extern char D_00136C70[];   /* DS1O_D.IRX */
extern char D_00136C90[];   /* USBD.IRX */
extern char D_00136CB0[];   /* PL2303.IRX */
extern char D_0013A048[];
extern char D_0013A050[];
extern char D_0013A058[];
extern char D_0013A060[];
extern char D_0013A068[];
extern char D_0013A070[];
void PutString(int a0, int a1, ...);
void PutStringS(int a0, int a1, ...);
int sceSifLoadModule(int a0, int a1, int a2);
void sceSifInitRpc(int mode);
int sceSifInitIopHeap(void);
int sceCdInit(int mode);
int sceCdMmode(int mode);
int sceSifRebootIop(const char *img);
int sceSifSyncIop(void);
void sceSifLoadFileReset(void);
void sceFsReset(void);
void PreparePowerOff(void);
int sceDmaReset(int mode);
int sceDbcInit(void);
void padsysInit(void);
void setNewIopIdentifier(const char *name);
int usbSerialSysInit(void);

/* LoaderSysLoadIopModule (003CB8) without the argument string: the original expands it in place. */
static __inline__ int load_module(char *path) {
    int r;

    PutString(0x4080FF00, (int)D_00136B00);
    PutString(0x80C0FF00, (int)D_0013A018, path);
    PutStringS(0x4080FF00, (int)D_0013A020);
    r = sceSifLoadModule((int)path, 0, 0);
    if (r < 0) {
        PutStringS(0xFF804000, (int)D_00136B10, path, r);
        return -1;
    }
    PutStringS(0x4080FF00, (int)D_0013A028);
    return 0;
}

static __inline__ void reboot_iop(char *img) {
    PutString(0xFFFF00, (int)D_00136AE8);
    PutString(0x40FFFF80, (int)D_0013A018, img);
    PutStringS(0xFFFF00, (int)D_0013A020);
    while (sceSifRebootIop(img) == 0)
        ;
    while (sceSifSyncIop() == 0)
        ;
    PutStringS(0xFFFF00, (int)D_0013A028);
}

#define LOAD(path, name)                                        \
    if (load_module(path) < 0)          \
        while (1)                                               \
            ;                                                   \
    setNewIopIdentifier(name)

int func_001033B0(void)
{
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    PutString(0xFFFFFF00, (int)D_00136B98);
    PutString(0x80FFC000, (int)D_0013A038, D_00136BB8, D_00136BC8);
    PutStringS(0xFFFFFF00, (int)D_0013A040);
    PutStringS(0x80C0FF00, (int)D_00136BD8);
    sceCdInit(0);
    sceCdMmode(2);
    PutStringS(0x80C0FF00, (int)D_0013A028);
    reboot_iop(D_00136BF8);
    sceSifInitRpc(0);
    sceSifLoadFileReset();
    sceFsReset();
    sceCdInit(0);
    sceCdMmode(2);
    PreparePowerOff();
    sceSifLoadFileReset();
    sceFsReset();
    sceDmaReset(1);
    LOAD(D_00136C10, D_0013A048);
    LOAD(D_00136C30, D_0013A050);
    LOAD(D_00136C50, D_0013A058);
    LOAD(D_00136C70, D_0013A060);
    sceSifLoadFileReset();
    sceFsReset();
    sceDmaReset(1);
    sceDbcInit();
    padsysInit();
    LOAD(D_00136C90, D_0013A068);
    LOAD(D_00136CB0, D_0013A070);
    return usbSerialSysInit();
}
