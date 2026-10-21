/* asm/cod/015940.s -> sceVibSetActParam.
 * SCE libvib sceVibSetActParam; size/n2 stores before the DbcParam bitfields, second memcpy destination as an int sum n2 + (int)&req + 8 (Session 41)
 * MATCHED. */
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

    size = 0x28;
    req.n2 = n2;
    p.f0 = 0xB;
    p.f1 = 1;
    p.f2 = 3;
    p.f3 = 1;
    func_0012821C(req.data, p2, n2);
    req.n1 = n1;
    func_0012821C((void *)(n2 + (int)&req + 8), p1, n1);
    return sceDbcSendData2(port, p, &size, &req);
}
