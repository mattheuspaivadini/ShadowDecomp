/* STATUS (Session 29, 2026-10-18): NON_MATCHING. best score 19 [cc=29].
 * Residual = the second memcpy destination: the original builds (n2 + sp) + 8 and reuses n2's register; every form tried folds n2 + 8 first (req.data + n2, &req.data[n2], (char *)&req + n2 + 8, char buf[0x30] with 5 index forms, a char *q temporary, unsigned memcpy size), plus the DbcParam mask in v0 vs t2. Statement order of n1/n2/size permuted.
 * The original .s stays in the build (asm/cod/015940.s); this C
 * draft (Session 29) is kept for the record. */
typedef struct {
    unsigned long f0:14;
    unsigned long f1:2;
    unsigned long f2:8;
    unsigned long f3:8;
} DbcParam;

struct VibActReq {
    int  n1;                    /* 0x00 */
    int  n2;                    /* 0x04 */
    unsigned char data[0x28];   /* 0x08 */
};

void *func_0012821C(void *dst, const void *src, int n);   /* memcpy */
int sceDbcSendData2(int port, DbcParam param, int *size, void *buf);

int sceVibSetActParam(int port, int n1, void *p1, int n2, void *p2) {
    DbcParam p;
    struct VibActReq req;
    int size;

    p.f0 = 0xB;
    p.f1 = 1;
    p.f2 = 3;
    p.f3 = 1;
    req.n2 = n2;
    size = 0x28;
    func_0012821C(req.data, p2, n2);
    req.n1 = n1;
    func_0012821C(req.data + n2, p1, n1);
    return sceDbcSendData2(port, p, &size, &req);
}
