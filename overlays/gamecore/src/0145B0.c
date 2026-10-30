/* GAMECORE.XFF @ 0x0145B0 (36 B) - nico_setFruitsFlag
 * Evidence: `jal GetScrLwsOriClass`, then two loads from the result
 * (+0x1224 -> $a1, +0x121C -> $a0) and a sibling `j` to `fruitsFlagSet`.
 * UNCONFIRMED: the two field meanings and the callee prototype.
 
 */
void *GetScrLwsOriClass(void);
void fruitsFlagSet(int a, int b);

void nico_setFruitsFlag(void) {
    char *lws = (char *)GetScrLwsOriClass();
    fruitsFlagSet(*(int *)(lws + 0x121C), *(int *)(lws + 0x1224));
}
