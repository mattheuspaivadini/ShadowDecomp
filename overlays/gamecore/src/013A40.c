/* GAMECORE.XFF @ 0x013A40 (40 B) - endingflowDecPlayerHpPersent
 * Evidence: the float argument is saved in `$f20` (`mov.s` in the `jal` delay
 * slot), `jal getPlayerHp`, `mul.s $f12, $f0, $f20`, then a sibling `j` to
 * `setPlayerHp` with the product.
 * UNCONFIRMED: the callee prototypes (both take/return the HP value).
 
 */
float getPlayerHp(void);
void setPlayerHp(float hp);

void endingflowDecPlayerHpPersent(float ratio) {
    setPlayerHp(getPlayerHp() * ratio);
}
