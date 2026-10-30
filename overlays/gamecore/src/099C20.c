/* GAMECORE.XFF @ 0x099C20 (12 B) - AI_InitSurpriseArrow
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void AI_InitSurpriseArrow(char *p) {
    F(p, int, 0) = 0;
    F(p, int, 4) = 0;
}
