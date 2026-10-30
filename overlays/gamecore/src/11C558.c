/* GAMECORE.XFF @ 0x11C558 (24 B) - SCRConditionSubFunc
 * Evidence: ops ld lw sd; calls j execCondition; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int execCondition(int a, int b);
int SCRConditionSubFunc(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
    return execCondition(a0, a8);
}
