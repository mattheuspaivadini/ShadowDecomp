/* KERNEL.XFF @ 0x026808 (168 B) - Sg2SepInit
 * Evidence: clears the 32 x 0x50-byte slots at .bss+0x971C0 (memset, then +0 = 0 and +0xC/+0x14/+0x18 = -1), sets .bss+0x97BC0 = 1 and installs the static tick handler .text+0x26568 through Sg2CtrlEntryTickProcById(1, ...). UNCONFIRMED: field names.
 * Levers: separate induction vars (q = b+0x10 as int*, byte offset off) to get s0/s2/s4; register int i asm("$17") and off asm("$18") fix the s1/s2/s3 allocation; the flag store goes BEFORE the call (it lands in the jal delay slot); (void *)(off + (int)b) fixes the addu operand order.
 * c_sources: 026808 = src/026808.c -G0 -fno-strict-aliasing
 */
struct SepSlot {
    int a0;
    int pad4[2];
    int m_c;
    int pad10;
    int n14;
    int n18;
    char rest[0x34];
};
extern struct SepSlot D_kernel_bss_971C0[32];
extern int D_kernel_bss_97BC0;
void *memset(void *p, int c, unsigned int n);
int Sg2CtrlEntryTickProcById(int id, void (*func)(void));
void func_026568(void);

int Sg2SepInit(void) {
    register int i __asm__("$17");
    register int off __asm__("$18") = 0;
    char *b = (char *)D_kernel_bss_971C0;
    int *q;

    q = (int *)(b + 0x10);
    for (i = 31; i >= 0; i--) {
        memset((void *)(off + (int)b), 0, 0x50);
        off += 0x50;
        q[-4] = 0;
        q[1] = -1;
        q[2] = -1;
        q[-1] = -1;
        q += 20;
    }
    D_kernel_bss_97BC0 = 1;
    Sg2CtrlEntryTickProcById(1, func_026568);
    return 0;
}
