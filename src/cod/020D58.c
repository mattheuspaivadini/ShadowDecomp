/* asm/cod/020D58.s -> _sceMcpIsSpeckOutClust.
 * sceMc2 sysinfo record; dtls13010 -g0
 * MATCHED. */
struct R020D58 {
    char pad00[0x2A];
    unsigned short w;   /* 0x2A */
    unsigned short d;   /* 0x2C */
    char pad2E[0x184 - 0x2E];
};

extern struct R020D58 gSceMc2SysInfo[];

int _sceMcpIsSpeckOutBlock(int index, int key);

int _sceMcpIsSpeckOutClust(int index, int a1) {
    struct R020D58 *r = &gSceMc2SysInfo[index];

    return _sceMcpIsSpeckOutBlock(index, a1 * r->w / r->d);
}
