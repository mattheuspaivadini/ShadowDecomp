/* GAMECORE.XFF @ 0x0CD738 (20 B) - sprWeaponGetMarkerPos
 * Evidence: ops lq sq; data <.data>+0x1A90
 * UNCONFIRMED: field names/types guessed from offsets
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 D_kernel_data_1A90;
void sprWeaponGetMarkerPos(u_long128 *out) {
    *out = D_kernel_data_1A90;
}
