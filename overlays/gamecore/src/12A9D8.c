/* GAMECORE.XFF @ 0x12A9D8 (44 B) - coliJudgeNotWater
 * Evidence: stores $ra, 0x0($sp); loads $v0, 0x0($v0), $ra, 0x0($sp); calls GetCollisionDBAttributeAdr; frame
 
 */
unsigned long long *GetCollisionDBAttributeAdr(void);

int coliJudgeNotWater(void) {
    return ((*GetCollisionDBAttributeAdr() & 0x7C00) ^ 0x4400) != 0;
}
