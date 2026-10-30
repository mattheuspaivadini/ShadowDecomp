/* GAMECORE.XFF @ 0x121C48 (52 B) - startHintWork
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls _gameIWorkChk, _gameIWorkSet; frame
 
 */
int _gameIWorkChk(int i);
void _gameIWorkSet(int i, int v);

void startHintWork(void) {
    if (_gameIWorkChk(0xE) == -1)
        _gameIWorkSet(0xE, 0);
}
