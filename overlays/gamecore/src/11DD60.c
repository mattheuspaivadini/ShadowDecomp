/* GAMECORE.XFF @ 0x11DD60 (56 B) - SCRConditionOverDistanceToPlayerWorldXZ
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x4080($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: +0x4080 is the XZ distance to the player. */
char *getSCRDataCtrlWork(void);

int SCRConditionOverDistanceToPlayerWorldXZ(float distance) {
    if (distance <= *(float *)(getSCRDataCtrlWork() + 0x4080))
        return 1;
    return 0;
}
