/* GAMECORE.XFF @ 0x02DFD8 (36 B) - time_attack_set_best_time
 * Evidence: `lw $a0, .bss+0x4CA0`, `swc1 $f12, .data+0x1078` (the float
 * argument stored verbatim), sibling `j` to `setBossIndexTimeAttackBestTime`
 * with that index and `$f12` still live.
 * UNCONFIRMED: field meanings (boss index, best-time slot) and prototypes.
 
 */
extern int D_kernel_bss_4CA0[];
extern float D_kernel_data_1078[];
void setBossIndexTimeAttackBestTime(int boss, float time);

void time_attack_set_best_time(float time) {
    D_kernel_data_1078[0] = time;
    setBossIndexTimeAttackBestTime(D_kernel_bss_4CA0[0], time);
}
