/* GAMECORE.XFF @ 0x070DE8 (36 B) - nico_delOmakeItem
 * Evidence: `jal gameflowSetPauseEnable` with `$a0 = 1` in the delay slot, then
 * `lw $a0, .data+0x148C` and a sibling `j` to `isysRequestDeleteObj`.
 * UNCONFIRMED: the .data field meaning (an object pointer) and the prototypes.
 
 */
extern char D_kernel_data_0000[];
void gameflowSetPauseEnable(int enable);
void isysRequestDeleteObj(void *obj);

void nico_delOmakeItem(void) {
    gameflowSetPauseEnable(1);
    isysRequestDeleteObj(*(void **)(D_kernel_data_0000 + 0x148C));
}
