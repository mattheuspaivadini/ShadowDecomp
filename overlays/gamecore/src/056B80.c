/* GAMECORE.XFF @ 0x056B80 (40 B) - home_test_anim
 * Evidence: `jal isysGetThisSubThread`, `jal scrInit` with that result, then
 * `jal scrRun` inside an endless `b` back to the `jal scrRun` (no return).
 * UNCONFIRMED: the callee prototypes.
 
 */
void *isysGetThisSubThread(void);
void scrInit(void *thread);
void scrRun(void);

void home_test_anim(void) {
    scrInit(isysGetThisSubThread());
    for (;;) {
        scrRun();
    }
}
