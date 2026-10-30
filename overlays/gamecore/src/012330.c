/* GAMECORE.XFF @ 0x012330 (48 B) - nico_SendSuicideMail
 * Evidence: `$a1 = $a0`, `$a2 = &InitialGeometryPointer`, `$a3 = -3`,
 * `$f12 = 0x477FFF00` (65535.0f) and a sibling `j` to `SendCharaAttackMsg`.
 * UNCONFIRMED: the geometry operand type and the callee prototype.
 
 */
extern float InitialGeometryPointer[];
void SendCharaAttackMsg(int a, int b, void *geom, int d, float e);

void nico_SendSuicideMail(int obj) {
    SendCharaAttackMsg(obj, obj, InitialGeometryPointer, -3, 65535.0f);
}
