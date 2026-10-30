/* GAMECORE.XFF @ 0x11DE08 (56 B) - SCRConditionLessDistanceToPlayerWorld
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x4084($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: same field as SCRConditionOverDistanceToPlayerWorld. */
char *getSCRDataCtrlWork(void);

int SCRConditionLessDistanceToPlayerWorld(float distance) {
    if (*(float *)(getSCRDataCtrlWork() + 0x4084) <= distance)
        return 1;
    return 0;
}
