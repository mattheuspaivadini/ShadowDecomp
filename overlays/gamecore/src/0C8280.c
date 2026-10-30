/* GAMECORE.XFF @ 0x0C8280 (24 B) - GetTimeAttackTimeLimit
 * Evidence: ops lwc1; data <.data>+0x1940
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern struct { int a, b, c, flags; float d, limit, timer; } D_kernel_data_1940;

float GetTimeAttackTimeLimit(void) {
    return D_kernel_data_1940.limit - D_kernel_data_1940.timer;
}
