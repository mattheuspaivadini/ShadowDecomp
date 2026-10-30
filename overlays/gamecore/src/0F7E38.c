/* GAMECORE.XFF @ 0x0F7E38 (64 B) - getAimPosFromPathManager
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp), $v1, 0x0($s0); loads $s0, 0x0($sp), $v1, 0x0($v1), $ra, 0x8($sp); calls <.text>; frame
 
 */
/* UNCONFIRMED: writes the aim position (16 B) read from passage work index 0. */
typedef unsigned int u_long128 __attribute__((mode(TI)));

char *getPassageWork(char *p, int idx);

int getAimPosFromPathManager(char *p, void *dst) {
    char *work = getPassageWork(p, 0);
    if (work == 0)
        return 0;
    *(u_long128 *)dst = *(u_long128 *)work;
    return 1;
}
