/* GAMECORE.XFF @ 0x0ADD70 (40 B) - Kite_InitKiteAdvertisePathWork
 * Evidence: stores $s0, 0x0($sp), $ra, 0x8($sp), $zero, 0x4($s0); loads $ra, 0x8($sp), $s0, 0x0($sp); calls <.text>; frame
 
 */
void func_000ACBF0(char *p);

void Kite_InitKiteAdvertisePathWork(char *p) {
    func_000ACBF0(p);
    *(int *)(p + 4) = 0;
}
