/* STATUS (Session 44, 2026-10-21): NON_MATCHING. best score 176 (was 230; sw.py diff lines).
 * sceNetcnfifGetResult declared int as defined (022378): 230 -> 176. Residual unchanged in kind: register allocation (type/ifc spilled in the image).
 * Fence grid (build/s42/fence_grid.py: empty asm "+r" / asm volatile "r" use of each local after each statement): best single fence.
 * netcnfif load_entry_auto: two lists, every error frees both, strcmp of ifc sys_name against
 * attach_ifc/attach_dev as two calls (keeps the type test in the loop). Residual = register
 * allocation (original spills type and ifc to the frame, copies the first count into s0). Tried:
 * opt mask variable, 40 declaration orders, size copy variable.
 * The original .s stays in the build (asm/cod/0225E8.s); this C
 * draft (Session 35) is kept for the record. */
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
    sceNetcnfifList_t *p, *ifc = 0, *dev = 0;
    int type, opt, sync, n, i, r;

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
    ifc_list = memalign(0x40, n * sizeof(sceNetcnfifList_t));
    asm volatile("" : : "r"(ifc_list));
    if (ifc_list == 0) {
        free(ifc_list);
        free(dev_list);
        return -2;
    }
    FlushCache(0);
    sceNetcnfifGetList(fname, type, ifc_list, n);
    while (sceNetcnfifSync(sync))
        ;
    sceNetcnfifGetResult(&if_arg);
    if (if_arg.data < 0) {
        free(ifc_list);
        free(dev_list);
        return -1;
    }
    for (i = 0, p = ifc_list; i < n; i++, p++) {
        if (func_00128E6C(usr_name, p->usr_name) == 0) {
            ifc = p;
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
    n = if_arg.data;
    if (n <= 0) {
        free(ifc_list);
        free(dev_list);
        return -1;
    }
    dev_list = memalign(0x40, n * sizeof(sceNetcnfifList_t));
    if (dev_list == 0) {
        free(ifc_list);
        free(dev_list);
        return -2;
    }
    FlushCache(0);
    sceNetcnfifGetList(fname, 0, dev_list, n);
    while (sceNetcnfifSync(sync))
        ;
    sceNetcnfifGetResult(&if_arg);
    if (if_arg.data < 0) {
        free(ifc_list);
        free(dev_list);
        return -1;
    }
    for (i = 0, p = dev_list; i < n; i++, p++) {
        FlushCache(0);
        sceNetcnfifLoadEntry(fname, 0, p->usr_name, data);
        while (sceNetcnfifSync(sync))
            ;
        sceNetcnfifGetResult(&if_arg);
        if (if_arg.data < 0) {
            free(ifc_list);
            free(dev_list);
            return -1;
        }
        if (type == 1)
            r = func_00128E6C(ifc->sys_name, data->attach_ifc);
        else
            r = func_00128E6C(ifc->sys_name, data->attach_dev);
        if (r == 0) {
            if (dev != 0) {
                free(ifc_list);
                free(dev_list);
                return -12;
            }
            dev = p;
        }
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
    free(ifc_list);
    free(dev_list);
    return 0;
}
