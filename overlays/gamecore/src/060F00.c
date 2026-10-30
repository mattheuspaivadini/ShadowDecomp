/* GAMECORE.XFF @ 0x060F00 (60 B) - IsGeoColStatus
 * Evidence: `jal nico_GetGeometryPointerAttr` with `$s0 = $a1`, `$s1 = $a2` in
 * the delay slot, then `and` with `$s0`, `xor` with `$s1` and
 * `sltiu $v0,$v0,1`.
 * UNCONFIRMED: the attribute bit meanings.
 
 */
int nico_GetGeometryPointerAttr(void *geom);

int IsGeoColStatus(void *geom, int mask, int status) {
    return ((nico_GetGeometryPointerAttr(geom) & mask) ^ status) == 0;
}
