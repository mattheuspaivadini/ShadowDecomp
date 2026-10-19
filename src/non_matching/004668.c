/* STATUS (Session 34, 2026-10-19): NON_MATCHING. best score 82 [cc=296].
 * loader network bring-up (load_set_conf_only, interface id, address). CD branch assigns path/name
 * before PutStringS. Residual = the original keeps D_0013D000 and +0x40 in s-regs from before memalign
 * and re-derives them later from the same %hi register; error printf tails are cross-jumped.
 * Tried: msg variable, per-error printf+return 0, static inline load/up helpers, block-scoped
 * cp/cpi/id locals (all 408-416 bytes against 428).
 * The original .s stays in the build (asm/cod/004668.s); this C
 * draft (Session 34) is kept for the record. */
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
extern int D_0013A180[2];
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
    r = -0x21F;
    if (buf != 0) {
        r = load_set_conf_only(cp, cpi, buf, path, name, flag);
        free(buf);
    }
    return r;
}

int func_00104668(int from_mc, int idx) {
    char *path;
    char *name;
    int flag = 0;
    const char *msg;
    char *cp = D_0013D000;
    char *cpi = cp + 0x40;

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
        msg = D_00137108;
    } else if (sceLibnetWaitGetInterfaceID(cp, cpi, &D_0013A180[1], 1) < 0) {
        msg = D_00137128;
    } else {
        sceInetCtlUpInterface(cp, cpi, D_0013A180[1]);
        if (sceLibnetWaitGetAddress(cp, cpi, &D_0013A180[1], 1, myaddr, 0) >= 0)
            return 1;
        msg = D_00137140;
    }
    func_001285C0(msg);
    return 0;
}
