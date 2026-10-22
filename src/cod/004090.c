/* asm/cod/004090.s -> func_00104090.
 * ldnet IOP module set per network type; LOAD macro, two switches (jtbl_00136FF0 + case tree) (Session 35)
 * MATCHED. */
extern char D_00136DE0[];
extern char D_00136E00[];
extern char D_00136E20[];
extern char D_00136E68[];
extern char D_00136E88[];
extern char D_00136EA0[];
extern char D_00136EC0[];
extern char D_00136EE0[];
extern char D_00136F00[];
extern char D_00136F20[];
extern char D_00136F40[];
extern char D_00136F60[];
extern char D_00136F78[];
extern char D_00136F98[];
extern char D_00136FB8[];
extern char D_00136FD8[];
extern char D_0013A088[];
extern char D_0013A090[];
extern char D_0013A098[];
extern char D_0013A0A0[];
extern char D_0013A0A8[];
extern char D_0013A0B0[];
extern char D_0013A0B8[];
extern char D_0013A0C0[];
extern char D_0013A0C8[];
extern char D_0013A0D0[];
extern char D_0013A0D8[];
extern char D_0013A0E0[];
int LoaderSysLoadIopModule(const char *path, int argc, const char *argp);
void setNewIopIdentifier(const char *name);

#define LOAD(path, argc, argp, name)                            if (LoaderSysLoadIopModule(path, argc, argp) < 0)               return -1;                                              setNewIopIdentifier(name)

int func_00104090(int type)
{
    LOAD(D_00136DE0, 0, 0, D_0013A088);         /* INET */
    LOAD(D_00136E00, 0x46, D_00136E20, D_0013A090);   /* NETCNF */
    LOAD(D_00136E68, 0x14, D_00136E88, D_0013A098);   /* INETCTL */
    switch (type) {
    case 1:
    case 2:
        LOAD(D_00136EA0, 0, 0, D_0013A0A0);     /* USBD */
        LOAD(D_00136EC0, 0, 0, D_0013A0A8);     /* AN986 */
        break;
    case 5:
        LOAD(D_00136EA0, 0, 0, D_0013A0A0);     /* USBD */
        break;
    case 3:
    case 4:
        LOAD(D_00136EE0, 0, 0, D_0013A0B0);     /* DEV9 */
        LOAD(D_00136F00, 0, 0, D_0013A0B8);     /* SMAP */
        break;
    case 0:
        break;
    }
    switch (type) {
    case 2:
    case 4:
        LOAD(D_00136F20, 0, 0, D_0013A0C0);     /* PPP */
        LOAD(D_00136F40, 0, 0, D_0013A0C8);     /* PPPOE */
        break;
    case 5:
        LOAD(D_00136F20, 0, 0, D_0013A0C0);     /* PPP */
        LOAD(D_00136F60, 1, D_0013A0D0, D_0013A0D0);
        break;
    case 0:
        LoaderSysLoadIopModule(D_00136EA0, 0, 0);
        LoaderSysLoadIopModule(D_00136EC0, 0, 0);
        LoaderSysLoadIopModule(D_00136EE0, 0, 0);
        LoaderSysLoadIopModule(D_00136F00, 0, 0);
        LoaderSysLoadIopModule(D_00136F20, 0, 0);
        LoaderSysLoadIopModule(D_00136F40, 0, 0);
        break;
    }
    LOAD(D_00136F78, 0, 0, D_0013A0D8);         /* MSIFRPC */
    LOAD(D_00136F98, 0, 0, D_0013A0E0);         /* LIBNET */
    LOAD(D_00136FB8, 0, 0, D_00136FD8);         /* NETCNFIF */
    return 0;
}
