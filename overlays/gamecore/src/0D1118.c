/* GAMECORE.XFF @ 0x0D1118 (44 B) - st_pausemenu_load_omake_chara
 * Evidence: `$s0 = $a0`, `jal gStatLoadPlayerAccessories`, `sw 1 -> 0x0($s0)`.
 * UNCONFIRMED: whether gStatLoadPlayerAccessories takes the forwarded argument
 
 */
void gStatLoadPlayerAccessories(void);

void st_pausemenu_load_omake_chara(int *p) {
    gStatLoadPlayerAccessories();
    *p = 1;
}
