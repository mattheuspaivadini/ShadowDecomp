/* GAMECORE.XFF @ 0x0FA0F8 (56 B) - getColiGroupByUserPathWork
 * Evidence: loads $v1, 0x3C50($a0); relocs gcGlobalVar
 
 */
/* UNCONFIRMED: +0x3C50 is a user path group id; the two group tables live at
 * gcGlobalVar+0x238 (id 0) and gcGlobalVar+0x234 (id 1).
 */
extern char gcGlobalVar[];

char *getColiGroupByUserPathWork(char *p) {
    int id = *(int *)(p + 0x3C50);
    if (id == 0)
        return gcGlobalVar + 0x238;
    if (id == 1)
        return gcGlobalVar + 0x234;
    return 0;
}
