/* KERNEL.XFF @ 0x000F40 (112 B) - iosEE2IopRequest
 * Evidence: a sceSifDmaData {src, dst, size, 0} on the stack; FlushCache(0); under the IOP semaphore sceSifSetDma(&d, 1) and spins while sceSifDmaStat(id) >= 0; FlushCache(0).
 */
typedef struct {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} sceSifDmaData;
void FlushCache(int op);
void iosWaitIopSema(void);
void iosSignalIopSema(void);
unsigned int sceSifSetDma(sceSifDmaData *sdd, int len);
int sceSifDmaStat(unsigned int id);

void iosEE2IopRequest(void *src, void *dst, int size) {
    sceSifDmaData d;
    unsigned int id;

    d.data = (unsigned int)src;
    d.addr = (unsigned int)dst;
    d.size = size;
    d.mode = 0;
    FlushCache(0);
    iosWaitIopSema();
    id = sceSifSetDma(&d, 1);
    while (sceSifDmaStat(id) >= 0) {
    }
    iosSignalIopSema();
    FlushCache(0);
}
