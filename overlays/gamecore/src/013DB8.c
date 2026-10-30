/* GAMECORE.XFF @ 0x013DB8 (20 B) - fadeChkStat
 * Evidence: (.data+0x774 & a0) != 0
 * UNCONFIRMED: none
 */
extern unsigned int D_kernel_data_0774[];

int fadeChkStat(unsigned int m) {
    return (D_kernel_data_0774[0] & m) != 0;
}
