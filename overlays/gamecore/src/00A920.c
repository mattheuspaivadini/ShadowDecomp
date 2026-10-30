/* GAMECORE.XFF @ 0x00A920 (56 B) - gamecore
 * Evidence: four `jal` calls (`initgc`, `initgcmain`, `initgcmaingp`,
 * `initgcchartest`) then `$v0 = 0`.
 * UNCONFIRMED: the callee prototypes.
 
 */
void initgc(void);
void initgcmain(void);
void initgcmaingp(void);
void initgcchartest(void);

int gamecore(void) {
    initgc();
    initgcmain();
    initgcmaingp();
    initgcchartest();
    return 0;
}
