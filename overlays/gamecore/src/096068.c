/* GAMECORE.XFF @ 0x096068 (32 B) - st_motionsyncanimation
 * Evidence: ops sd; calls <.text>, isysSleepSubThread; frame
 * UNCONFIRMED: callee func_00096088 unnamed static
 */
void func_00096088(void);
void isysSleepSubThread(void);

void st_motionsyncanimation(void) {
    while (1) {
        func_00096088();
        isysSleepSubThread();
    }
}
