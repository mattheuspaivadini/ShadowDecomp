/* GAMECORE.XFF @ 0x0F7DF0 (24 B) - getPathColiGroup
 * Evidence: ops ld lw sd; calls j <.text>; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
int func_000F7E08(int g);
int getPathColiGroup(char *p) {
    return func_000F7E08(F(p, int, 0x3C50));
}
