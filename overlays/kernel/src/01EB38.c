/* KERNEL.XFF @ 0x01EB38 (72 B) - iosFreeIopHeap
 * Evidence: under the IOP semaphore: sceSifFreeIopHeap(p), then LoaderSysDeleteExternalIopMemoryList(p) < 0 ? -1 : 0 (ret = 0 then conditional -1: li -1 + movz).
 */
void iosWaitIopSema(void);
void iosSignalIopSema(void);
int sceSifFreeIopHeap(void *p);
int LoaderSysDeleteExternalIopMemoryList(void *p);

int iosFreeIopHeap(void *p) {
    int ret;

    iosWaitIopSema();
    sceSifFreeIopHeap(p);
    ret = 0;
    if (LoaderSysDeleteExternalIopMemoryList(p) < 0) {
        ret = -1;
    }
    iosSignalIopSema();
    return ret;
}
