/* GAMECORE.XFF @ 0x107A30 (52 B) - deleteGazeCtrlWork
 * Evidence: stores $ra, 0x0($sp), $zero, 0x40($v1); loads $v0, 0x40($v1), $ra, 0x0($sp); calls j DeleteTwoWayLink; frame
 
 */
/* UNCONFIRMED: +0x40 is the gaze link id, +0x34 the link node. */
void DeleteTwoWayLink(void *node);

void deleteGazeCtrlWork(char *p) {
    if (*(int *)(p + 0x40) != 0) {
        *(int *)(p + 0x40) = 0;
        DeleteTwoWayLink(p + 0x34);
    }
}
