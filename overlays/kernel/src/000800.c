/* KERNEL.XFF @ 0x000800 (88 B) - iosCreateIdleThread
 * Evidence: iosCreateMsgQueue(&.bss+0x8070, 0, 0); iosCreateThread(static .text+0x8D8, stack .bss+0x8090, 0x1000, prio 0x7D, 0) stored to .bss+0x9090; sibling iosStartThread(id, 0). UNCONFIRMED: prototypes of the ios thread helpers and object names.
 */
extern char D_kernel_bss_8070[];
extern char D_kernel_bss_8090[];
extern int D_kernel_bss_9090;
void iosCreateMsgQueue(void *queue, int a, int b);
int iosCreateThread(void (*func)(void), void *stack, int size, int prio, int arg);
void iosStartThread(int thread, int arg);
void func_0008D8(void);

void iosCreateIdleThread(void) {
    int id;

    iosCreateMsgQueue(D_kernel_bss_8070, 0, 0);
    id = iosCreateThread(func_0008D8, D_kernel_bss_8090, 0x1000, 0x7D, 0);
    D_kernel_bss_9090 = id;
    iosStartThread(id, 0);
}
