/* GAMECORE.XFF @ 0x03B198 (32 B) - getPinAttackIKWorkSize
 * Evidence: jal ...NbOptionNodes; sll 6
 * UNCONFIRMED: none
 */
int GetCharacterClassInitParamNbOptionNodes(int c);

int getPinAttackIKWorkSize(int c) {
    return GetCharacterClassInitParamNbOptionNodes(c) << 6;
}
