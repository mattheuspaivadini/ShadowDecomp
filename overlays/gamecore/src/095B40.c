/* GAMECORE.XFF @ 0x095B40 (32 B) - scrRun
 * Evidence: ops ld sd; calls isysGetThisSubThread, j <.text>; frame
 * UNCONFIRMED: callee func_000953F0 unnamed static
 */
int isysGetThisSubThread(void);
void func_000953F0(int thread);

void scrRun(void) {
    func_000953F0(isysGetThisSubThread());
}
