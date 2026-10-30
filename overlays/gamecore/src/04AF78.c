/* GAMECORE.XFF @ 0x04AF78 (40 B) - CheckDeathTentacle
 * Evidence: `lw .data+0x1100`; `beqz` jumps to the `return 1` block, otherwise
 * the slot is cleared and 0 is returned.
 * UNCONFIRMED: the slot meaning (a pending death-tentacle request).
 
 */
extern int D_kernel_data_1100[];

int CheckDeathTentacle(void) {
    if (D_kernel_data_1100[0] != 0) {
        D_kernel_data_1100[0] = 0;
        return 0;
    }
    return 1;
}
