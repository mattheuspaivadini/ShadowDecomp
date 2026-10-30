/* GAMECORE.XFF @ 0x124130 (48 B) - updateAttackWaistIKWork
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp), $v0, 0x0($v1); loads $v1, 0x1110($v0), $ra, 0x8($sp), $v0, 0x0($s0), $s0, 0x0($sp); calls GetCharacterClass; frame
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
int GetCharacterClass(int obj);

void updateAttackWaistIKWork(int obj, u_long128 *src) {
    int cls = GetCharacterClass(obj);
    u_long128 *dst = *(u_long128 **)(cls + 0x1110);
    *dst = *src;
}
