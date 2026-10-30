/* GAMECORE.XFF @ 0x042A80 (44 B) - SCRGetCharNodePos
 * Evidence: `$t0 = 1` (5th integer argument), `$a3 = [a2+8]`, `$a2 = $a1`,
 * `$a1 = $a0`, `$a0 = $sp` (a 16-byte stack buffer) before `jal
 * GetMotionNodeQuaternionPos`; the buffer is not returned.
 * UNCONFIRMED: the field meaning and the callee prototype.
 
 */
void GetMotionNodeQuaternionPos(void *out, void *a, void *b, int node,
                                int flag);

void SCRGetCharNodePos(void *a, void *b, void *c) {
    char buf[16];

    GetMotionNodeQuaternionPos(buf, a, b, *(int *)((char *)c + 8), 1);
}
