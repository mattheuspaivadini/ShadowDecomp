/* asm/cod/015210.s -> scePad2Read.
 * scePad2Read; PadRec/PadFrame structs, frame length cached in a local for the copy (Session 22)
 * MATCHED. */
struct PadRec {
    int open;                /* 0x00 */
    int ready;               /* 0x04 */
    int frame;               /* 0x08 */
    int f0C;                 /* 0x0C */
    unsigned char *buf;      /* 0x10 */
    unsigned char f14[0x320];/* 0x14 */
};
struct PadFrame {
    unsigned char f00;
    unsigned char f01;
    unsigned char len;       /* 0x02 */
    unsigned char f03;
    int valid;               /* 0x04 */
    char pad08[0x14];
    unsigned char data[1];   /* 0x1C */
};

extern struct PadRec D_0014B598[];

int func_00115650(int index);
struct PadFrame *func_001156A8(int index);
void *func_0012821C(void *dst, const void *src, int n);
int func_001157D8(unsigned char *a, unsigned char *b);

int scePad2Read(int port, unsigned char *rdata) {
    struct PadFrame *p;
    int len;

    if (D_0014B598[port].open == 0)
        return -1;
    if (D_0014B598[port].ready == 0 && func_00115650(port) < 0)
        return -1;
    p = func_001156A8(port);
    len = p->len;
    if (len != 0 && p->data != 0) {
        func_0012821C(rdata, p->data, len);
        func_001157D8(&p->data[p->len], D_0014B598[port].f14);
    }
    if (p->valid == 0)
        return -1;
    return p->len;
}
