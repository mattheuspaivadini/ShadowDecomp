/* GAMECORE.XFF @ 0x119098 (32 B) - setConditionBoss
 * Evidence: ops ld sd; calls execCondition, j setConditionResultBoss; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int execCondition(int a, int b);
void setConditionResultBoss(int r);
void setConditionBoss(int a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    setConditionResultBoss(execCondition(a0, a6));
}
