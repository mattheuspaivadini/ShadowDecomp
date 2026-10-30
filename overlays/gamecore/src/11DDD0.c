/* GAMECORE.XFF @ 0x11DDD0 (56 B) - SCRConditionOverDistanceToPlayerWorld
 * Evidence: stores $f20, 0x8($sp), $ra, 0x0($sp); loads $f0, 0x4084($v0), $ra, 0x0($sp), $f20, 0x8($sp); calls getSCRDataCtrlWork; frame
 
 */
/* UNCONFIRMED: +0x4084 is the 3D distance to the player. */
char *getSCRDataCtrlWork(void);

int SCRConditionOverDistanceToPlayerWorld(float distance) {
    if (distance <= *(float *)(getSCRDataCtrlWork() + 0x4084))
        return 1;
    return 0;
}
