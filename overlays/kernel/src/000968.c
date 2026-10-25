/* KERNEL.XFF @ 0x000968 (52 B) - iosInit
 * Evidence: four `jal`s with empty delay slots and a sibling `j iosCreateIopMgr`;
 * no arguments are set up.
 */
void iosInitThreadSystem(void);
void iosInitMessageSystem(void);
void iosCreateIdleThread(void);
void iosCreatePrintMgr(void);
void iosCreateIopMgr(void);

void iosInit(void) {
    iosInitThreadSystem();
    iosInitMessageSystem();
    iosCreateIdleThread();
    iosCreatePrintMgr();
    iosCreateIopMgr();
}
