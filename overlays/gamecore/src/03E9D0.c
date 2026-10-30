/* GAMECORE.XFF @ 0x03E9D0 (44 B) - SCRGetBossCollisionAttribute
 * Evidence: `jal GetDamageClass`, `$a1 = $v0 + 0x10`, `jal
 * GetGeometryPointerSurfaceAttribute` with `$a0 = $sp` (a 8-byte stack result),
 * then `ld $v0, 0($sp)`.
 * UNCONFIRMED: the field/attribute meanings and the callee prototypes.
 
 */
void *GetDamageClass(void);
void GetGeometryPointerSurfaceAttribute(long *out, void *geom);

long SCRGetBossCollisionAttribute(void) {
    long attr;

    GetGeometryPointerSurfaceAttribute(&attr, (char *)GetDamageClass() + 0x10);
    return attr;
}
