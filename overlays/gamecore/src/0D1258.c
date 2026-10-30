/* GAMECORE.XFF @ 0x0D1258 (16 B) - isInLoadWait
 * Evidence: ops lw; data <.data>+0x1B48
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern int D_kernel_data_1B48;

int isInLoadWait(void) {
    return D_kernel_data_1B48 == 0;
}
