/* GAMECORE.XFF @ 0x11FCC8 (44 B) - SCRConditionArrowParentOverNum
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $s0, 0x0($sp), $ra, 0x8($sp); calls getArrowObjParent; frame
 
 */
int getArrowObjParent(void);

int SCRConditionArrowParentOverNum(void *unused, int num) {
    return getArrowObjParent() >= num;
}
