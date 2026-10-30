/* GAMECORE.XFF @ 0x11EFF8 (48 B) - SCRConditionMyselfPartsDamaged
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls getBossPartsCurDamage; frame
 
 */
/* UNCONFIRMED: the parts-work pointer reaches the callee in $a1 but nothing in
 * this function computes it; it is modelled as a global register variable in
 * $t1 ($9), which reproduces the image's lone `move $a1,$t1` delay slot.
 */
float getBossPartsCurDamage(void *work, int parts);

register int parts_work asm("$9");

int SCRConditionMyselfPartsDamaged(void *work) {
    return getBossPartsCurDamage(work, parts_work) != 0.0f;
}
