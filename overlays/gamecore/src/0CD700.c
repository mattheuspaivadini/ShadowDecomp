/* GAMECORE.XFF @ 0x0CD700 (56 B) - sprWeaponSetMarker
 * Evidence: `beqz $a2` and `beqz $a0` both skip to the final `sw $a2 -> [.data+0x1AB0]`;
 * body does `lq/sq` 16-byte copies from $a0 to <.data>+0x1A90 and from $a1 to
 * <.data>+0x1AA0.
 * UNCONFIRMED: field meanings; the 128-bit globals are declared as u_long128 arrays
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 D_kernel_data_1A90[];
extern u_long128 D_kernel_data_1AA0[];
extern int D_kernel_data_1AB0;

void sprWeaponSetMarker(u_long128 *a0, u_long128 *a1, int a2) {
    if (a2 != 0 && a0 != 0) {
        D_kernel_data_1A90[0] = a0[0];
        D_kernel_data_1AA0[0] = a1[0];
    }
    D_kernel_data_1AB0 = a2;
}
