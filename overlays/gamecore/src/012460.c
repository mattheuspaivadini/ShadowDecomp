/* GAMECORE.XFF @ 0x012460 (60 B) - nico_GetCharacterParentGPAttr
 * Evidence: `jal GetCharacterClass` with `$s0 = $a1` in the delay slot, a
 * null-tested `lw 0x124($a0)`, then `ld 0x690($a0)` ANDed with the mask.
 * UNCONFIRMED: the class fields at +0x124 and +0x690.
 
 */
void *GetCharacterClass(void *chara);

long nico_GetCharacterParentGPAttr(void *chara, long mask) {
    void *cls = GetCharacterClass(chara);

    if (*(int *)((char *)cls + 0x124) == 0)
        return 0;
    return *(long *)((char *)cls + 0x690) & mask;
}
