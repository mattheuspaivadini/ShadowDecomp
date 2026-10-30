/* GAMECORE.XFF @ 0x04B7A8 (32 B) - dischargeTerm
 * Evidence: jal getSpecialEffectObjWork; a0=[v0+0x10]; sibling j isysRequestDeleteObj
 * UNCONFIRMED: none
 */
int *getSpecialEffectObjWork(int a);
void isysRequestDeleteObj(int o);

void dischargeTerm(int a) {
    isysRequestDeleteObj(getSpecialEffectObjWork(a)[4]);
}
