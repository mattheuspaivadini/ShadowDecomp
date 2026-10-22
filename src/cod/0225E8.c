/* asm/cod/0225E8.s -> sceNetcnfifLoadEntryAuto.
 * netcnfif load_entry_auto; separate counts per list, an int p reused as size copy and list walker, attach-name mismatch via continue in both type arms, two no-code X refs on dev (fp vs stack for ifc) (Session 46)
 * MATCHED. */
typedef struct {
    int data;
    int f_no_decode;
    int type;
    int addr;
    char pad[0x300];
} sceNetcnfifArg_t;

typedef struct {
    int type;
    int stat;
    char sys_name[256];         /* 0x008 */
    char usr_name[256];         /* 0x108 */
    char pad[0x240 - 0x208];
} sceNetcnfifList_t;

typedef struct {
    char attach_ifc[256];       /* 0x000 */
    char attach_dev[256];       /* 0x100 */
} sceNetcnfifData_t;

void free(void *p);
void *memalign(int align, int size);
int FlushCache(int mode);
void sceNetcnfifGetCount(char *fname, int type);
int sceNetcnfifSync(int mode);
int sceNetcnfifGetResult(sceNetcnfifArg_t *result);
void sceNetcnfifGetList(char *fname, int type, sceNetcnfifList_t *addr, int size);
void sceNetcnfifLoadEntry(char *fname, int type, char *usr_name, sceNetcnfifData_t *data);
int func_00128E6C(const char *a, const char *b);   /* strcmp */

int sceNetcnfifLoadEntryAuto(char *fname, int flags, char *usr_name, sceNetcnfifData_t *data)
{
    sceNetcnfifArg_t if_arg;
    sceNetcnfifList_t *ifc_list = 0, *dev_list = 0;
    sceNetcnfifList_t *ifc = 0, *dev = 0;
    int p;
    int type, opt, sync, n, m, i;

    type = flags & 0xFFFF;
    opt = flags & 0xFFFF0000;
    sync = 1;
    if (type != 1 && type != 2) {
        free(ifc_list);
        free(dev_list);
        return -10;
    }
    if (opt & 0x10000)
        sync = 0;

    sceNetcnfifGetCount(fname, type);
    while (sceNetcnfifSync(sync))
        ;
    sceNetcnfifGetResult(&if_arg);
    n = if_arg.data;
    if (n <= 0) {
        free(ifc_list);
        free(dev_list);
        return -1;
    }
    p = n;      /* p first holds the list size, then walks the list as an int (keeps the image copy of n) */
    ifc_list = memalign(0x40, p * sizeof(sceNetcnfifList_t));
    if (ifc_list == 0) {
        free(ifc_list);
        free(dev_list);
        return -2;
    }
    FlushCache(0);
    sceNetcnfifGetList(fname, type, ifc_list, p);
    while (sceNetcnfifSync(sync))
        ;
    sceNetcnfifGetResult(&if_arg);
    if (if_arg.data < 0) {
        free(ifc_list);
        free(dev_list);
        return -1;
    }
    for (p = (int)ifc_list, i = 0; i < n; p += sizeof(sceNetcnfifList_t), i++) {
        if (func_00128E6C(usr_name, ((sceNetcnfifList_t *)p)->usr_name) == 0) {
            ifc = (sceNetcnfifList_t *)p;
            break;
        }
    }
    if (ifc == 0) {
        free(ifc_list);
        free(dev_list);
        return -8;
    }

    sceNetcnfifGetCount(fname, 0);
    while (sceNetcnfifSync(sync))
        ;
    sceNetcnfifGetResult(&if_arg);
    m = if_arg.data;
    if (m <= 0) {
        free(ifc_list);
        free(dev_list);
        return -1;
    }
    dev_list = memalign(0x40, m * sizeof(sceNetcnfifList_t));
    if (dev_list == 0) {
        free(ifc_list);
        free(dev_list);
        return -2;
    }
    FlushCache(0);
    sceNetcnfifGetList(fname, 0, dev_list, m);
    while (sceNetcnfifSync(sync))
        ;
    sceNetcnfifGetResult(&if_arg);
    if (if_arg.data < 0) {
        free(ifc_list);
        free(dev_list);
        return -1;
    }
    for (i = 0, p = (int)dev_list; i < m; i++, p += sizeof(sceNetcnfifList_t)) {
        FlushCache(0);
        sceNetcnfifLoadEntry(fname, 0, ((sceNetcnfifList_t *)p)->usr_name, data);
        while (sceNetcnfifSync(sync))
            ;
        sceNetcnfifGetResult(&if_arg);
        if (if_arg.data < 0) {
            free(ifc_list);
            free(dev_list);
            return -1;
        }
        if (type == 1) {
            if (func_00128E6C(ifc->sys_name, data->attach_ifc) != 0) continue;
        } else if (func_00128E6C(ifc->sys_name, data->attach_dev) != 0) continue;
        if (dev != 0) {
            free(ifc_list);
            free(dev_list);
            return -12;
        }
        dev = (sceNetcnfifList_t *)p;
        asm volatile("" : : "X"(dev), "X"(dev));    /* no code: two more refs give dev a saved register (fp) and leave ifc on the stack */
    }
    if (dev == 0) {
        free(ifc_list);
        free(dev_list);
        return -8;
    }
    FlushCache(0);
    sceNetcnfifLoadEntry(fname, 0, dev->usr_name, data);
    while (sceNetcnfifSync(sync))
        ;
    sceNetcnfifGetResult(&if_arg);
    if (if_arg.data < 0) {
        free(ifc_list);
        free(dev_list);
        return -1;
    }
    asm volatile("" : : "X"(dev_list));
    free(ifc_list);
    free(dev_list);
    return 0;
}
