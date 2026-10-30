/* GAMECORE.XFF @ 0x0C9AA0 (52 B) - title_newfile
 * Evidence: stores $ra, 0x0($sp), $zero, 0x19C4($v0), $zero, 0x19D0($v1); loads $ra, 0x0($sp), $a0, 0x0($v0); relocs <.data>, <.data>+0x19C4, <.data>+0x19D0, ScrIntrDef_GAME_NEWSTART, ScrIntrDef_GAME_NEWSTART+0x0; calls setGameHardMode, j scriptIntrSignal; frame
 
 */
void setGameHardMode(int hard);
void scriptIntrSignal(int id);
extern int D_kernel_data_19C4;
extern int D_kernel_data_19D0;
extern int ScrIntrDef_GAME_NEWSTART;

void title_newfile(void) {
    D_kernel_data_19C4 = 0;
    D_kernel_data_19D0 = 0;
    setGameHardMode(0);
    scriptIntrSignal(ScrIntrDef_GAME_NEWSTART);
}
