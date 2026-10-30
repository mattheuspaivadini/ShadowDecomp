/* GAMECORE.XFF @ 0x00BF10 (28 B) - gcCreateScriptObj
 * Evidence: t2=t3=0 then sibling j createScriptObj
 * UNCONFIRMED: param count/types
 */
int createScriptObj(int, int, int, int, int, int, int, int);

int gcCreateScriptObj(int a, int b, int c, int d, int e, int f) {
    return createScriptObj(a, b, c, d, e, f, 0, 0);
}
