/* KERNEL.XFF @ 0x020070 (68 B) - Sg2ExStAdpcmWorkClear
 * Evidence: memset(w, 0, 0x2E0), then w[0] = 0 and words +8/+0xC = arg. UNCONFIRMED: layout.
 */
void *memset(void *p, int c, unsigned int n);

void Sg2ExStAdpcmWorkClear(int *w, int arg) {
    memset(w, 0, 0x2E0);
    w[0] = 0;
    w[2] = arg;
    w[3] = arg;
}
