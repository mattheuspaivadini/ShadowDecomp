/* GAMECORE.XFF @ 0x099A38 (28 B) - AI_InitAnimalOptimize
 * Evidence: ops sw swc1
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void AI_InitAnimalOptimize(char *p) {
    F(p, int, 0) = 1;
    F(p, float, 4) = 30.0f;
    F(p, int, 8) = 0;
}
