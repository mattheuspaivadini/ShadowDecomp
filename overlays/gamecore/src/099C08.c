/* GAMECORE.XFF @ 0x099C08 (20 B) - AI_InitGexCommonWork
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void AI_InitGexCommonWork(char *p) {
    F(p, int, 8) = 0;
    F(p, int, 0) = 0;
    F(p, int, 4) = 0;
    F(p, int, 0xC) = 0;
}
