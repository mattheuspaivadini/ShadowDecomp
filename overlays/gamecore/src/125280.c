/* GAMECORE.XFF @ 0x125280 (44 B) - initBeardIKWork
 * Evidence: stores $zero, 0x0($a2)
 
 */
void initBeardIKWork(void *a, void *b, char *p) {
    int i = 9;
    char *q = p + 0x3B0;
    do {
        i--;
        *(int *)q = 0;
        q -= 0x60;
    } while (i >= 0);
}
