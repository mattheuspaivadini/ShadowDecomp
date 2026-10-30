/* GAMECORE.XFF @ 0x019D08 (60 B) - gStatUnloadHorseChara
 * Evidence: `$s0 = .data+0x9E4`, `lw 0x0($s0)` guard, `jal
 * stagemanager_unloadstagecore` with the value in `$a0`, and the `sw $zero`
 * placed *outside* the guard (it is the `beqz` target).
 * UNCONFIRMED: the `.data` slot's name.
 
 */
extern char D_kernel_data_0000[];
void stagemanager_unloadstagecore(void *stage);

void gStatUnloadHorseChara(void) {
    int *slot = (int *)(D_kernel_data_0000 + 0x9E4);

    if (*slot != 0)
        stagemanager_unloadstagecore((void *)*slot);
    *slot = 0;
}
