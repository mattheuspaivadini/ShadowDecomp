/* GAMECORE.XFF @ 0x11FC98 (48 B) - SCRConditionOverGameWork
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp); loads $s0, 0x0($sp), $ra, 0x8($sp); calls _gameWorkChk; frame
 
 */
int _gameWorkChk(int id);

int SCRConditionOverGameWork(void *unused, int id, int num) {
    return _gameWorkChk(id) >= num;
}
