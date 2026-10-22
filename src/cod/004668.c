/* asm/cod/004668.s -> func_00104668.
 * loader net bring-up; load_conf returns early on memalign failure (no if-then block for CSE to skip, so the second D_0013D000 keeps only the hi() from gcse), interface id is its own .sbss word D_0013A184 (Session 46)
 * MATCHED. */
extern char D_00137080[];   /* "cdrom0:\SETTING\NET.DB;1" */
extern char D_001370A0[];   /* "from CD default..." */
extern char D_001370B8[];   /* "from memory card..." */
extern char D_001370D0[];   /* "mc0:/BWNETCNF/BWNETCNF" */
extern char D_001370E8[];   /* "ldnet: up interface no auto\n" */
extern char D_00137108[];   /* "load_set_conf_only() failed.\n" */
extern char D_00137128[];   /* "get_interface_id()\n" */
extern char D_00137140[];   /* "wait_get_addr_only() failed.\n" */
extern char *D_00131FA0[];
extern char *D_00131FB8[];
extern char D_0013D000[];
extern int D_0013A184;
extern char myaddr[];

void PutStringS(int color, const char *fmt, ...);
int func_001285C0(const char *fmt, ...);   /* printf */
void *memalign(int align, int size);
void free(void *p);
int load_set_conf_only(void *cp, void *cpi, void *buf, const char *path, const char *name, int flag);
int sceLibnetWaitGetInterfaceID(void *cp, void *cpi, int *id, int n);
int sceInetCtlUpInterface(void *cp, void *cpi, int id);
int sceLibnetWaitGetAddress(void *cp, void *cpi, int *id, int n, void *addr, int flag);

static inline int load_conf(char *path, char *name, int flag) {
    char *cp = D_0013D000;
    char *cpi = cp + 0x40;
    void *buf;
    int r;

    buf = memalign(0x40, 0x1340);
    if (buf == 0)
        return -0x21F;
    r = load_set_conf_only(cp, cpi, buf, path, name, flag);
    free(buf);
    return r;
}

int func_00104668(int from_mc, int idx) {
    char *path;
    char *name;
    int flag = 0;
    char *cp;
    char *cpi;
    int *id;

    if (from_mc == 0) {
        path = D_00137080;
        name = D_00131FA0[idx];
        PutStringS(0x80FF8000, D_001370A0);
    } else {
        PutStringS(0x8080FF00, D_001370B8);
        path = D_001370D0;
        name = D_00131FB8[idx];
        flag = 1;
    }
    func_001285C0(D_001370E8);
    if (load_conf(path, name, flag) < 0) {
        func_001285C0(D_00137108);
        return 0;
    }
    cp = D_0013D000;
    cpi = cp + 0x40;
    id = &D_0013A184;
    if (sceLibnetWaitGetInterfaceID(cp, cpi, id, 1) < 0) {
        func_001285C0(D_00137128);
        return 0;
    }
    sceInetCtlUpInterface(cp, cpi, D_0013A184);
    if (sceLibnetWaitGetAddress(cp, cpi, id, 1, myaddr, 0) < 0) {
        func_001285C0(D_00137140);
        return 0;
    }
    return 1;
}
