/* GAMECORE.XFF @ 0x031560 (48 B) - st_unload_horse_char
 * Evidence: `jal isysGetThisSubThread` (result saved in `$s0` in the delay slot
 * of the next call), `jal gStatUnloadHorseChara` with `$a0` untouched, then a
 * sibling `j` to `isysRequestDeleteObj` with `$a0 = $s0`.
 * UNCONFIRMED: the callee prototypes.
 
 */
void *isysGetThisSubThread(void);
void gStatUnloadHorseChara(void);
void isysRequestDeleteObj(void *thread);

void st_unload_horse_char(void) {
    void *thread = isysGetThisSubThread();

    gStatUnloadHorseChara();
    isysRequestDeleteObj(thread);
}
