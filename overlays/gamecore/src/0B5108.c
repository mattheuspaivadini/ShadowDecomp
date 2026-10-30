/* GAMECORE.XFF @ 0x0B5108 (24 B) - gextailStopColProc
 * Evidence: ops ld sd; calls j SetCharacterObjCollisionProcFlag; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void SetCharacterObjCollisionProcFlag(int a, int f);
void gextailStopColProc(int a) {
    SetCharacterObjCollisionProcFlag(a, 0);
}
