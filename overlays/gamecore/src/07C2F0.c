/* GAMECORE.XFF @ 0x07C2F0 (64 B) - SCRPlayerCallHorseEnd
 * Evidence: `jal GetSCRCharaAIWorkPtr` (result parked in `$s0` via the next
 * call's delay slot), `jal get_main_cameraman`, then
 * `jal get_game_camera` with `$a0` = the cameraman result, then
 * `jal end_object_interest_game_camera` with `$a0` = the camera result, and
 * finally `sb $zero, 0xD9C($s0)`.
 * UNCONFIRMED: the AI work byte at +0xD9C.
 
 */
void *GetSCRCharaAIWorkPtr(void);
void *get_main_cameraman(void);
void *get_game_camera(void *cameraman);
void end_object_interest_game_camera(void *camera);

void SCRPlayerCallHorseEnd(void) {
    char *work = GetSCRCharaAIWorkPtr();
    void *cameraman = get_main_cameraman();

    end_object_interest_game_camera(get_game_camera(cameraman));
    work[0xD9C] = 0;
}
