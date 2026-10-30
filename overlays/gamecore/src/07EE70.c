/* GAMECORE.XFF @ 0x07EE70 (24 B) - player_setHellDangerPoint
 * Evidence: a1 += 0x70, sibling j to ParentLayoutObj with a0 live
 * UNCONFIRMED: callee signature/arg types guessed
 */
void ParentLayoutObj(int a, char *b);
void player_setHellDangerPoint(int a, char *b) { ParentLayoutObj(a, b + 0x70); }
