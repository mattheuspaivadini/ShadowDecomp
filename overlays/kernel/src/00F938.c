/* KERNEL.XFF @ 0x00F938 (56 B) - CopyMultiQuaternion
 * Evidence: counted loop copying n 128-bit elements with lq/sq (index * 16).
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void CopyMultiQuaternion(u_long128 *d, u_long128 *s, int n) {
    int i;

    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}
