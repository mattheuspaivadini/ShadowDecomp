/* GAMECORE.XFF @ 0x0F8178 (52 B) - deleteUserPathWork
 * Evidence: stores $ra, 0x0($sp), $zero, 0xA4($v1); loads $v0, 0xA4($v1), $ra, 0x0($sp); calls j DeleteTwoWayLink; frame
 
 */
/* UNCONFIRMED: +0xA4 is the user path link id, +0x98 the link node. */
void DeleteTwoWayLink(void *node);

void deleteUserPathWork(char *p) {
    if (*(int *)(p + 0xA4) != 0) {
        *(int *)(p + 0xA4) = 0;
        DeleteTwoWayLink(p + 0x98);
    }
}
