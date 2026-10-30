/* KERNEL.XFF @ 0x02E608 (232 B) - func_02E608 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing] (58/58 words)
 * Evidence: record = base + idx * 0xC4 (sll/addu chain); DIntr() result kept in $s2; clears the record
 * words +0x14..+0x44 (+0x34 = -1, four float 0.0f from $f20); IirInit(rec + 0x48), IirInit(rec + 0x90),
 * IirParam(rec + 0x48 / + 0x90, 0.0f, 0.0f, 1); tail `j EIntr` when DIntr() returned non-zero.
 * Levers: one-argument IirInit prototype (a two-argument one adds a1/a2 zeroing, 236 B); the run of
 *   stores ends with q[12] = 0 - the scheduler emits the last store of the run first and reorg puts
 *   q[11] = 0 in the first IirInit delay slot (session 76 worker f reached 10/58, store order closed it).
 * UNCONFIRMED: function name, IirInit/IirParam prototypes (IirInit is not in the lane yet), field meanings.
 */

extern int DIntr(void);
extern void EIntr(void);
extern void IirInit(void *f);
extern void IirParam(void *f, float a, float b, int c);

void func_02E608(char *base, int idx)
{
    char *p;
    int r, *q;
    float z;
    p = base + idx * 0xC4;
    r = DIntr();
    z = 0.0f;
    q = (int *)(p + 0x14);
    q[8] = -1;
    q[0] = 0;
    q[2] = 0;
    ((float *)q)[6] = z;
    ((float *)q)[5] = z;
    ((float *)q)[4] = z;
    ((float *)q)[3] = z;
    q[7] = 0;
    q[10] = 0;
    q[11] = 0;
    q[12] = 0;
    IirInit(p + 0x48);
    IirInit(p + 0x90);
    IirParam(p + 0x48, z, z, 1);
    IirParam(p + 0x90, z, z, 1);
    if (r) EIntr();
}
