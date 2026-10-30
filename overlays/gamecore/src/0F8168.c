/* GAMECORE.XFF @ 0x0F8168 (12 B) - setPassageCallBack
 * Evidence: ops sw
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void setPassageCallBack(char *p, int a, int b) {
    F(p, int, 0x3C44) = b;
    F(p, int, 0x3C48) = a;
}
