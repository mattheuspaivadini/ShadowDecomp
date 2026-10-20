/* asm/cod/00F590.s -> func_0010F590.
 * SCE libkernl TLB set-up for 32 MB machines (called by InitTLB when
 * GetMemorySize() == 0x2000000; UNCONFIRMED name InitTLB32MB, as in the SDK):
 * print the layout, Wired = 0, load the kernel/default entries of TLBInfo,
 * Wired = count, then the extended entries, and fill the rest of the 48
 * entries with invalid 0xE0000000 + i * 0x2000 pages (func_0010F4B0 is the
 * syscall 0x56 TLB writer). The index lives in $t9 across the calls, so it is
 * a register asm local; that also makes gcc return the (i << 13) giv.
 * MATCHED. */
struct TLBEntry {
    unsigned int PageMask;      /* 0x00 */
    unsigned int EntryHi;       /* 0x04 */
    unsigned int EntryLo0;      /* 0x08 */
    unsigned int EntryLo1;      /* 0x0C */
};

struct TLBInfo {
    int NumKernelTLBEntries;            /* 0x00 */
    int NumDefaultTLBEntries;           /* 0x04 */
    int NumExtendedTLBEntries;          /* 0x08 */
    int NumWiredEntries;                /* 0x0C */
    struct TLBEntry *kernelTLB;         /* 0x10 */
    struct TLBEntry *defaultTLB;        /* 0x14 */
    struct TLBEntry *extendedTLB;       /* 0x18 */
};

extern struct TLBInfo TLBInfo;
extern char D_001381D0[];   /* "# TLB spad=0 kernel=1:%d default=%d:%d extended=%d:%d\n" */
extern char D_00138208[];   /* "# TLB over flow (1)" */
extern char D_00138220[];   /* "# TLB over flow (2)" */
extern char D_00138238[];   /* "# TLB over flow (3)" */

int kprintf(const char *fmt, ...);
void Exit(int status);
int func_0010F4B0(int index, unsigned int pagemask, unsigned int hi, unsigned int lo0, unsigned int lo1);

int func_0010F590(void) {
    register int i __asm__("$25");
    int n;
    struct TLBEntry *e;
    int j;

    kprintf(D_001381D0, TLBInfo.NumKernelTLBEntries - 1, TLBInfo.NumKernelTLBEntries,
            TLBInfo.NumKernelTLBEntries + TLBInfo.NumDefaultTLBEntries - 1,
            TLBInfo.NumKernelTLBEntries + TLBInfo.NumDefaultTLBEntries,
            TLBInfo.NumKernelTLBEntries + TLBInfo.NumDefaultTLBEntries + TLBInfo.NumExtendedTLBEntries - 1);
    __asm__ __volatile__ ("mtc0 $0, $6\n\tsync.p");

    n = TLBInfo.NumKernelTLBEntries;
    i = 0;
    if (n > 0x30) {
        kprintf(D_00138208);
        Exit(1);
    }
    for (e = TLBInfo.kernelTLB; i < n; i++, e++)
        func_0010F4B0(i, e->PageMask, e->EntryHi, e->EntryLo0, e->EntryLo1);

    n = i + TLBInfo.NumDefaultTLBEntries;
    if (n > 0x30) {
        kprintf(D_00138220);
        Exit(1);
    }
    for (e = TLBInfo.defaultTLB; i < n; i++, e++)
        func_0010F4B0(i, e->PageMask, e->EntryHi, e->EntryLo0, e->EntryLo1);

    TLBInfo.NumWiredEntries = i;
    __asm__ __volatile__ ("mtc0 %0, $6\n\tsync.p" : : "r" (i));

    if (TLBInfo.NumExtendedTLBEntries > 0) {
        n = i + TLBInfo.NumExtendedTLBEntries;
        if (n > 0x30) {
            kprintf(D_00138238);
            Exit(1);
        }
        for (e = TLBInfo.extendedTLB; i < n; i++, e++)
            func_0010F4B0(i, e->PageMask, e->EntryHi, e->EntryLo0, e->EntryLo1);
    }

    for (j = i; j < 0x30; j++)
        func_0010F4B0(j, 0, 0xE0000000 + (j << 13), 0, 0);
    return i;
}
