/* GAMECORE.XFF @ 0x1190D8 (28 B) - SCRFuncSetGameWork
 * Evidence: ops ld sd; calls j _gameWorkSet; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void _gameWorkSet(int n, int v);
void SCRFuncSetGameWork(int a, int n, int v) {
    _gameWorkSet(n, v);
}
