/* GAMECORE.XFF @ 0x116D50 (24 B) - SCRFuncSubFunc
 * Evidence: ops ld sd; calls j execSCRBaseFunc; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void execSCRBaseFunc(int a, int b);
void SCRFuncSubFunc(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7) {
    execSCRBaseFunc(a0, a7);
}
