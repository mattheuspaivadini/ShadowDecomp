/* GAMECORE.XFF @ 0x118EC8 (64 B) - SCRFuncSegmentUnloadRequest
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $s0, 0x0($sp), $ra, 0x8($sp); calls stagemanager_checkstageAlreadyLoadRequestedByStrptr, j stagemanager_unloadstageByStrptr; frame
 
 */
/* UNCONFIRMED: only the 7th argument ($t2) is used; the first six are the
 * generic script function parameters.
 */
int stagemanager_checkstageAlreadyLoadRequestedByStrptr(char *str);
void stagemanager_unloadstageByStrptr(char *str);

void SCRFuncSegmentUnloadRequest(void *a0, void *a1, void *a2, void *a3,
                                 void *t0, void *t1, char *str) {
    if (stagemanager_checkstageAlreadyLoadRequestedByStrptr(str))
        stagemanager_unloadstageByStrptr(str);
}
