/* GAMECORE.XFF @ 0x02E1C8 (28 B) - time_attack_begin
 * Evidence: frame, HI16/LO16 load of `ScrIntrDef_TIMEATTACK_MENU_START` into
 * $a0, then the sibling `j scriptIntrSignal`.
 */
extern int ScrIntrDef_TIMEATTACK_MENU_START;
int scriptIntrSignal(int id);

void time_attack_begin(void) {
    scriptIntrSignal(ScrIntrDef_TIMEATTACK_MENU_START);
}
