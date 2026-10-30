/* GAMECORE.XFF @ 0x099C38 (24 B) - AI_CheckNearArrow
 * Evidence: ops ld lwc1 sd; calls j chkNearStickArrow; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
#define F(p, T, o) (*(T *)((char *)(p) + (o)))
void chkNearStickArrow(int a, int b, char *c, float f);
void AI_CheckNearArrow(int a, int b, char *c) {
    chkNearStickArrow(a, b, c, F(c, float, 4));
}
