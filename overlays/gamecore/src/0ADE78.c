/* GAMECORE.XFF @ 0x0ADE78 (24 B) - Kite_SetSpecialPathLayout
 * Evidence: ops ld sd; calls j AI_SetAnimalLayout; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));
void AI_SetAnimalLayout(char *p, u_long128 *v, float a, float b);
void Kite_SetSpecialPathLayout(char *p, u_long128 *v, float a, float b) {
    AI_SetAnimalLayout(p + 0x1F0, v, a, b);
}
