/* GAMECORE.XFF @ 0x07C3F8 (44 B) - SCRPlayerBeginAccumulateAttack
 * Evidence: `sw 1` into AI work +0xD8C, then `lw $a0,
 * SCameraLwsAnimationParam_PLAYER_ACCUMULATE_ATTACK_CAM_VIB` (a named .data
 * word) and a sibling `j` to `boot_camera_lws_animation_by_script`.
 * UNCONFIRMED: the AI work field meaning and the callee prototype.
 
 */
void *GetSCRCharaAIWorkPtr(void);
extern int SCameraLwsAnimationParam_PLAYER_ACCUMULATE_ATTACK_CAM_VIB;
void boot_camera_lws_animation_by_script(int param);

void SCRPlayerBeginAccumulateAttack(void) {
    *(int *)((char *)GetSCRCharaAIWorkPtr() + 0xD8C) = 1;
    boot_camera_lws_animation_by_script(
        SCameraLwsAnimationParam_PLAYER_ACCUMULATE_ATTACK_CAM_VIB);
}
