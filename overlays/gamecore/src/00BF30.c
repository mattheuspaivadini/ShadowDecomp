/* GAMECORE.XFF @ 0x00BF30 (28 B) - _gcCreateChildScriptObj
 * Evidence: t2=t3, t3=0 then sibling j createScriptObj
 * UNCONFIRMED: param count/types
 */
int createScriptObj(int, int, int, int, int, int, int, int);

int _gcCreateChildScriptObj(int a, int b, int c, int d, int e, int f, int g, int h) {
    return createScriptObj(a, b, c, d, e, f, h, 0);
}
