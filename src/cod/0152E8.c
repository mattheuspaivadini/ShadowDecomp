/* asm/cod/0152E8.s -> scePad2GetButtonProfile.
 * scePad2GetButtonProfile; profile copied from frame data + len, commutative addu operand order via int arithmetic (Session 22)
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
    unsigned char plen;      /* 0x03 */
    int valid;               /* 0x04 */
    char pad08[0x14];
    unsigned char data[1];   /* 0x1C */
};

extern struct PadRec D_0014B598[];

int func_00115650(int index);
struct PadFrame *func_00115710(int index);
int scePad2GetState(int port);
void *func_0012821C(void *dst, const void *src, int n);
int func_001157D8(unsigned char *a, unsigned char *b);

int scePad2GetButtonProfile(int port, unsigned char *profile) {
    struct PadFrame *p;
    int len;

    scePad2GetState(port);
    if (D_0014B598[port].ready == 0 && func_00115650(port) < 0)
        return -1;
    p = func_00115710(port);
    len = p->plen;
    if (len != 0 && p->data != 0) {
        func_0012821C(profile, (unsigned char *)(p->len + (int)p) + 0x1C, len);
        func_001157D8(p->data + p->len, D_0014B598[port].f14);
    }
    if (p->valid == 0)
        return -1;
    return p->plen;
}
