/* GAMECORE.XFF @ 0x044B88 (16 B) - is_LwsOrientObj
 * Evidence: lbu [a0+8]; xori 0x16; sltiu 1
 * UNCONFIRMED: none
 */
int is_LwsOrientObj(unsigned char *p) {
    return p[8] == 0x16;
}
