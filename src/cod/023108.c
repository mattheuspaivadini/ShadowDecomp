/* asm/cod/023108.s -> sceNetcnfifSendIOP.
 * sceNetcnfifSendIOP; sceSifDmaData + ternary align (Session 23)
 * MATCHED. */
typedef struct { unsigned int data; unsigned int addr; unsigned int size; unsigned int mode; } sceSifDmaData;
int FlushCache(int x);
unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);
int sceNetcnfifSendIOP(unsigned int data, unsigned int addr, unsigned int size) {
    sceSifDmaData sdd;
    unsigned int s;
    sdd.data = data; sdd.addr = addr;
    s = size & 0xffffffc0; sdd.size = (size & 0x3f) == 0 ? s : s + 0x40;
    sdd.mode = 0;
    FlushCache(0);
    return sceSifSetDma(&sdd, 1);
}
