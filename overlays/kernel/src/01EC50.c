/* KERNEL.XFF @ 0x01EC50 (72 B) - iosGetIopTotalFreeMemSize
 * Evidence: under the IOP semaphore: sceSifInitRpc(0); sceSifInitIopHeap(); returns sceSifQueryTotalFreeMemSize().
 */
void iosWaitIopSema(void);
void iosSignalIopSema(void);
void sceSifInitRpc(unsigned int mode);
int sceSifInitIopHeap(void);
int sceSifQueryTotalFreeMemSize(void);

int iosGetIopTotalFreeMemSize(void) {
    int size;

    iosWaitIopSema();
    sceSifInitRpc(0);
    sceSifInitIopHeap();
    size = sceSifQueryTotalFreeMemSize();
    iosSignalIopSema();
    return size;
}
