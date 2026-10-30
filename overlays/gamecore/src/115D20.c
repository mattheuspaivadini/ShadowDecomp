/* GAMECORE.XFF @ 0x115D20 (60 B) - SCRFuncSetAttainLostPlayerPosGlobalY
 * Evidence: stores $ra, 0x10($sp), $f20, 0x18($sp), $v1, 0x0($sp), $f20, 0x4($sp); loads $v1, 0x4030($v0), $ra, 0x10($sp), $f20, 0x18($sp); calls getSCRDataCtrlWork, setAttainmentPos; frame
 
 */
/* UNCONFIRMED: +0x4030 is the last known player position vector; only the Y
 * component is replaced by the script value.
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

char *getSCRDataCtrlWork(void);
void setAttainmentPos(char *work, void *pos);

void SCRFuncSetAttainLostPlayerPosGlobalY(float y) {
    char *work = getSCRDataCtrlWork();
    u_long128 pos = *(u_long128 *)(work + 0x4030);
    *(float *)((char *)&pos + 4) = y;
    setAttainmentPos(work, &pos);
}
