/* GAMECORE.XFF @ 0x11F028 (48 B) - SCRConditionMyselfWeakDamaged
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls getBossWeakCurDamage; frame
 
 */
/* UNCONFIRMED: same $t1 ($9) global-register model as SCRConditionMyselfPartsDamaged. */
float getBossWeakCurDamage(void *work, int weak);

register int weak_work asm("$9");

int SCRConditionMyselfWeakDamaged(void *work) {
    return getBossWeakCurDamage(work, weak_work) != 0.0f;
}
