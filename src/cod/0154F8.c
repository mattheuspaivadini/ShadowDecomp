/* asm/cod/0154F8.s -> scePad2GetButtonInfo.
 * scePad2GetButtonInfo; BtnInfo struct copy + switch on the button type under a valid check (Session 22)
 * MATCHED. */
struct BtnInfo {
    int valid;      /* 0x0 */
    int type;       /* 0x4 */
    int offset;     /* 0x8 */
    int shift;      /* 0xC */
};
struct PadRec {
    int open;                /* 0x00 */
    int ready;               /* 0x04 */
    int frame;               /* 0x08 */
    int f0C;                 /* 0x0C */
    unsigned char *buf;      /* 0x10 */
    struct BtnInfo btn[50];  /* 0x14 */
    char pad[0x334 - 0x14 - 50 * 16];
};
extern struct PadRec D_0014B598[];

int scePad2GetButtonInfo(int port, unsigned char *rdata, int id) {
    struct BtnInfo b;
    int v;

    b = D_0014B598[port].btn[id];
    if (b.valid != 0) {
        switch (b.type) {
        case 1:
        if ((rdata[b.offset] >> b.shift) & 1)
            return 0;
        return 1;
        case 8:
        v = (rdata[b.offset] >> b.shift) & 0xFF;
        if (b.shift != 0) {
            b.offset++;
            v = (v | (rdata[b.offset] << (8 - b.shift))) & 0xFF;
        }
        return v;
        }
    }
    return -1;
}
