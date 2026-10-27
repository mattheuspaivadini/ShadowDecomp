/* KERNEL.XFF @ 0x01FF10 (28 B) - Sg2ExStAdpcmQuit
 * Evidence: the static at .text+0x20000 then sibling Sg2StAdpcmQuit().
 */
void func_020000(void);
void Sg2StAdpcmQuit(void);

void Sg2ExStAdpcmQuit(void) {
    func_020000();
    Sg2StAdpcmQuit();
}
