/* GAMECORE.XFF @ 0x01E590 (24 B) - getPlayerMaxHp
 * Evidence: frame, `$a0 = 0xB` before the sibling `j _gameFWorkChk`; the callee
 * result is returned unchanged.
 */
int _gameFWorkChk(int id);

int getPlayerMaxHp(void) {
    return _gameFWorkChk(0xB);
}
