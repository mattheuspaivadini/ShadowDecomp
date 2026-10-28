/* KERNEL.XFF @ 0x01FF50 (172 B) - Sg2ExStAdpcmSlotReserv
 * Evidence: term = (term != 0) once; n times Sg2SlotFreeSearchTerm(term); for each slot != -1: Sg2SlotBlock(3, slot), count++, reserve flag [slot] = 1 (48 words at .bss+0x7F600); returns the count. UNCONFIRMED: argument names.
 */
extern int D_kernel_bss_7F600[48];
int Sg2SlotFreeSearchTerm(int term);
void Sg2SlotBlock(int mode, int slot);

int Sg2ExStAdpcmSlotReserv(int term, int n) {
    int cnt = 0;
    int t;
    int slot;
    int i;

    t = term != 0;
    for (i = 0; i < n; i++) {
        slot = Sg2SlotFreeSearchTerm(t);
        if (slot != -1) {
            Sg2SlotBlock(3, slot);
            cnt++;
            D_kernel_bss_7F600[slot] = 1;
        }
    }
    return cnt;
}
