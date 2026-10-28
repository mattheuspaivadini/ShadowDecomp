/* KERNEL.XFF @ 0x019468 (92 B) - getTWH
 * Evidence: smallest i in 0..10 with n <= (1 << i) (first iteration peeled: 1 < n), -1 when none; results <= 0 become 1. Texture width/height exponent. UNCONFIRMED: name meaning (TW/TH of a GS TEX0).
 */
int getTWH(int n) {
    int r = -1;
    int i;

    for (i = 0; i < 11; i++) {
        if (n <= (1 << i)) {
            r = i;
            break;
        }
    }
    if (r <= 0) {
        r = 1;
    }
    return r;
}
