/* GAMECORE.XFF @ 0x013DD0 (60 B) - fadeWait
 * Evidence: `lw .data+0x770` guard, `jal scrRun`, reload and `bnez` back to
 * the call; `$s0` holds the `.data` base.
 * UNCONFIRMED: the `.data` flag's name.
 
 */
extern char D_kernel_data_0000[];
void scrRun(void);

void fadeWait(void) {
    while (*(int *)(D_kernel_data_0000 + 0x770) != 0)
        scrRun();
}
