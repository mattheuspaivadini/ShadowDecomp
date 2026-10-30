/* GAMECORE.XFF @ 0x0419D8 (32 B) - nico_commonBossAI_home
 * Evidence: jal isysGetThisSubThread (result unused), a0=1, sibling j scrRunM
 * UNCONFIRMED: scrRunM arg list
 */
int isysGetThisSubThread(void);
void scrRunM(int a);

void nico_commonBossAI_home(void) {
    isysGetThisSubThread();
    scrRunM(1);
}
