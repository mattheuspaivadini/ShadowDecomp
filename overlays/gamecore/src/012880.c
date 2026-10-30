/* GAMECORE.XFF @ 0x012880 (36 B) - st_changePlayerInspireLevel
 * Evidence: frame 0x10 + `sd $ra`, `$a0 -> $a1`, `$a0 = .text+0x128A8`
 * (HI16/LO16 relocs against the unnamed static), `$a2 = 0`, then a sibling `j`
 * to `stagemanager_createsubthread`.
 * UNCONFIRMED: callee prototype, the static callback at .text+0x128A8 and the
 * meaning of the forwarded argument.
 
 */
void func_000128A8(void);
void stagemanager_createsubthread(void (*func)(void), int level, int flag);

void st_changePlayerInspireLevel(int level) {
    stagemanager_createsubthread(func_000128A8, level, 0);
}
