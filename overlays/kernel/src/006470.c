/* KERNEL.XFF @ 0x006470 (340 B) - iosInitThreadSystem
 * Evidence: clears the thread table (.bss+0xB1A0, 0x400) and the 32 0x2C-byte thread records (.bss+0xAC20), points each record's +8 at its 0x30-byte ThreadParam (.bss+0xA620), builds the free list (.bss+0xB5A0 head, next +0x20 / prev +0x1C, used list .bss+0xB5A4 empty), creates the manager thread iosCreateThread(.text+0x6308, stack .bss+0xB5B0, 0x2000, 2, 0) into .bss+0xD5B0 and StartThread's it (or the current thread when creation failed). UNCONFIRMED: names.
 */
struct ThreadParam {
    char pad[0x30];
};
struct IosThread {
    int uid;
    int id;
    struct ThreadParam *param;
    char padC[0x10];
    struct IosThread *prev;
    struct IosThread *next;
    char pad24[8];
};
extern struct IosThread *D_kernel_bss_B1A0[256];
extern struct IosThread D_kernel_bss_AC20[32];
extern struct ThreadParam D_kernel_bss_A620[32];
extern struct IosThread *D_kernel_bss_B5A0;
extern struct IosThread *D_kernel_bss_B5A4;
extern struct IosThread *D_kernel_bss_D5B0;
extern char D_kernel_bss_B5B0[];
void *memset(void *d, int c, unsigned int n);
struct IosThread *iosCreateThread(void (*func)(void), void *stack, int size, int prio, int arg);
int GetThreadId(void);
int StartThread(int id, void *arg);
void func_00006308(void);

void iosInitThreadSystem(void) {
    struct IosThread *th;
    int i;

    memset(D_kernel_bss_B1A0, 0, sizeof(D_kernel_bss_B1A0));
    memset(D_kernel_bss_AC20, 0, sizeof(D_kernel_bss_AC20));
    for (i = 0; i < 32; i++) {
        D_kernel_bss_AC20[i].param = &D_kernel_bss_A620[i];
    }
    D_kernel_bss_B5A0 = D_kernel_bss_AC20;
    D_kernel_bss_B5A4 = 0;
    for (i = 0; i < 31; i++) {
        D_kernel_bss_AC20[i].next = &D_kernel_bss_AC20[i + 1];
    }
    D_kernel_bss_AC20[31].next = 0;
    D_kernel_bss_AC20[0].prev = 0;
    for (i = 1; i < 32; i++) {
        D_kernel_bss_AC20[i].prev = &D_kernel_bss_AC20[i - 1];
    }
    D_kernel_bss_D5B0 = iosCreateThread(func_00006308, D_kernel_bss_B5B0, 0x2000, 2, 0);
    th = D_kernel_bss_D5B0;
    if (th == 0) {
        th = D_kernel_bss_B1A0[GetThreadId()];
    }
    StartThread(th->id, 0);
}
