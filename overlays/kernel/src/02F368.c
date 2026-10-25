/* KERNEL.XFF @ 0x02F368 (140 B) - Sg2ExPcmInputSetAutoFilter
 * Evidence: -2 for ch >= 4; n = static .text+0x2EA30 (type); n == -1 is returned as is; f >= n gives -2; otherwise the static .text+0x2E8A0 gets (static .text+0x2EA80 (type, f), ch, type, f); returns 0. UNCONFIRMED: callee names.
 */
int func_02EA30(int type);
void *func_02EA80(int type, int f);
void func_02E8A0(void *flt, int target, int type, int f);

int Sg2ExPcmInputSetAutoFilter(unsigned int ch, int type, int f) {
    int n;

    if (ch >= 4) {
        return -2;
    }
    n = func_02EA30(type);
    if (n == -1) {
        return n;
    }
    if (f >= n) {
        return -2;
    }
    func_02E8A0(func_02EA80(type, f), ch, type, f);
    return 0;
}
