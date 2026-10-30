/* GAMECORE.XFF @ 0x0F23E0 (36 B) - act_camera_cutout_game_camera_param_manager
 * Evidence: loads $a0, 0x8($a0), $v1, 0x1360($a1)
 
 */
/* UNCONFIRMED: work+8 holds the cut-out param id, +0x1360 the active camera mode. */
int act_camera_cutout_game_camera_param_manager(char *work, char *p) {
    int param = *(int *)(work + 8);
    if (param == 1 && *(int *)(p + 0x1360) == param)
        return 1;
    return 0;
}
