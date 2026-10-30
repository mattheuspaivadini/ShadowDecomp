/* GAMECORE.XFF @ 0x1190B8 (32 B) - setConditionHorse
 * Evidence: ops ld sd; calls execCondition, j setConditionResultHorse; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
int execCondition(int a, int b);
void setConditionResultHorse(int r);
void setConditionHorse(int a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    setConditionResultHorse(execCondition(a0, a6));
}
