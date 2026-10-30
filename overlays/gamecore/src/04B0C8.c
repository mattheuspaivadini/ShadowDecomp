/* GAMECORE.XFF @ 0x04B0C8 (40 B) - AI_GetBaseWorkSize
 * Evidence: `$a0 * 4 + 0xD6` (via `sll 2`), `blez $a1` skipping the extra part,
 * and the strength-reduced `$a0 * 48` (`(($a0 * 2) + $a0) << 4`) plus 0x33 in a
 * single addition chain (`addu $v0, $v1, $v0` then `addiu $v1, $v0, 0x33`).
 * UNCONFIRMED: the unit sizes and the second argument's meaning.
 
 */
int AI_GetBaseWorkSize(int count, int extra) {
    int size = count * 4 + 0xD6;

    if (extra > 0) {
        size = size + count * 48 + 0x33;
    }
    return size;
}
