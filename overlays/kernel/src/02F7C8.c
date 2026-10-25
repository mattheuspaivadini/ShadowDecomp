/* KERNEL.XFF @ 0x02F7C8 (108 B) - Sg2ExPcmOutputSetAutoFilter
 * Evidence: as Sg2ExPcmInputSetAutoFilter for the output (target 5, no channel check).
 */
int func_02EA30(int type);
void *func_02EA80(int type, int f);
void func_02E8A0(void *flt, int target, int type, int f);

int Sg2ExPcmOutputSetAutoFilter(int type, int f) {
    int n = func_02EA30(type);

    if (n == -1) {
        return n;
    }
    if (f >= n) {
        return -2;
    }
    func_02E8A0(func_02EA80(type, f), 5, type, f);
    return 0;
}
