/* KERNEL.XFF @ 0x01EAE0 (88 B) - iosAllocIopHeap
 * Evidence: sceSifAllocIopHeap(size) under iosWaitIopSema/iosSignalIopSema; a non-NULL block is also registered with LoaderSysEntryExternalIopMemoryList under the semaphore.
 */
void iosWaitIopSema(void);
void iosSignalIopSema(void);
void *sceSifAllocIopHeap(int size);
void LoaderSysEntryExternalIopMemoryList(void *p);

void *iosAllocIopHeap(int size) {
    void *p;

    iosWaitIopSema();
    p = sceSifAllocIopHeap(size);
    iosSignalIopSema();
    if (p != 0) {
        iosWaitIopSema();
        LoaderSysEntryExternalIopMemoryList(p);
        iosSignalIopSema();
    }
    return p;
}
