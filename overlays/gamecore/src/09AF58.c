/* GAMECORE.XFF @ 0x09AF58 (56 B) - AI_PlayerParentFlag
 * Evidence: `$s0 = $a0`, `jal GetLayoutClass` with `$a0 = $a1` in the delay
 * slot, `jal GetGeometryPointerObject` with `$a0 = $v0 + 0xC0`, then
 * `xor $v0,$v0,$s0` + `sltiu $v0,$v0,1` (pointer equality).
 * UNCONFIRMED: parameter types
 
 */
void *GetLayoutClass(void *obj);
void *GetGeometryPointerObject(void *p);

int AI_PlayerParentFlag(void *obj, void *layout) {
    return GetGeometryPointerObject((char *)GetLayoutClass(layout) + 0xC0) == obj;
}
