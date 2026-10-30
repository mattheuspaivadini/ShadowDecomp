/* GAMECORE.XFF @ 0x009CD0 (20 B) - GAMEUTIL_set_custom_boss_interest_position
 * Evidence: lq/sq 16-byte copy to .data+0x240
 * UNCONFIRMED: none
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern u_long128 D_kernel_data_0240[];

void GAMEUTIL_set_custom_boss_interest_position(u_long128 *src) {
    D_kernel_data_0240[0] = *src;
}
