/* GAMECORE.XFF @ 0x107C10 (20 B) - getGazeToolPos
 * Evidence: ops lq sq; data <.bss>+0x1F30
 * UNCONFIRMED: field names/types guessed from offsets
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 D_kernel_bss_21F30;
void getGazeToolPos(u_long128 *out) {
    *out = D_kernel_bss_21F30;
}
