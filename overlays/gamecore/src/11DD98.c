/* GAMECORE.XFF @ 0x11DD98 (56 B) - SCRConditionLessDistanceToPlayerWorldXZ
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x4080($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: same field as SCRConditionOverDistanceToPlayerWorldXZ. */
char *getSCRDataCtrlWork(void);

int SCRConditionLessDistanceToPlayerWorldXZ(float distance) {
    if (*(float *)(getSCRDataCtrlWork() + 0x4080) <= distance)
        return 1;
    return 0;
}
