/* KERNEL.XFF @ 0x016270 (188 B) - ClearVRAM
 * Evidence: a 0x40000-byte rootPtn buffer (iosMallocAlign align 16) with its first 4 bytes cleared; 16 times sceGsSetDefLoadImage(&li, dbp, 4, 0, 0, 0, 256, 256) (dbp a separate int stepped by 0x400 and narrowed to short), FlushCache(0), sceGsExecLoadImage(&li, buf), sceGsSyncPath(0, 0); then iosFree. UNCONFIRMED: sceGsLoadImage kept opaque (0x60 bytes).
 */
typedef struct {
    char pad[0x60];
} sceGsLoadImage;
extern char rootPtn[];
void *iosMallocAlign(void *ptn, int size, int align);
void iosFree(void *p);
void *memset(void *p, int c, unsigned int n);
int sceGsSetDefLoadImage(sceGsLoadImage *lp, short dbp, short dbw, short dpsm, short x, short y, short w, short h);
int FlushCache(int mode);
int sceGsExecLoadImage(sceGsLoadImage *lp, void *src);
void sceGsSyncPath(int mode, unsigned short timeout);

void ClearVRAM(void) {
    sceGsLoadImage li;
    void *buf;
    int i;
    int dbp = 0;

    buf = iosMallocAlign(rootPtn, 0x40000, 0x10);
    memset(buf, 0, 4);
    for (i = 0; i < 16; i++) {
        sceGsSetDefLoadImage(&li, dbp, 4, 0, 0, 0, 0x100, 0x100);
        FlushCache(0);
        sceGsExecLoadImage(&li, buf);
        sceGsSyncPath(0, 0);
        dbp += 0x400;
    }
    iosFree(buf);
}
