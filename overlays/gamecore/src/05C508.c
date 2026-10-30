/* GAMECORE.XFF @ 0x05C508 (40 B) - SCRConditionPlayerNippingHorseAndWall
 * Evidence: `jal getSCRDataCtrlWork`, `lw $a0, 0x4078($v0)` in the next `jal`
 * delay slot, then `sltu $v0, $zero, $v0` (result != 0).
 * UNCONFIRMED: the work field meaning and the callee prototypes.
 
 */
void *getSCRDataCtrlWork(void);
int nico_playerCheckNippingWithHorseAndWall(void *obj);

int SCRConditionPlayerNippingHorseAndWall(void) {
    return nico_playerCheckNippingWithHorseAndWall(
               *(void **)((char *)getSCRDataCtrlWork() + 0x4078)) != 0;
}
