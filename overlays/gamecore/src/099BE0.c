/* GAMECORE.XFF @ 0x099BE0 (28 B) - AI_InitAnimalWork
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void AI_InitAnimalWork(char *p, int a) {
    F(p, int, 4) = -1;
    F(p, int, 0xC) = 0;
    F(p, int, 8) = -1;
    F(p, int, 0) = a;
    F(p, int, 0x10) = 0;
}
