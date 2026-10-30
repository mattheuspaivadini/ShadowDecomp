/* GAMECORE.XFF @ 0x0C52B0 (48 B) - CheckSwordIndicateAimPoint
 * Evidence: stores $ra, 0x0($sp); loads $v0, 0x1934($v1), $ra, 0x0($sp); relocs <.data>, <.data>+0x1934; calls GAMEUTIL_is_player_obj; frame
 * The `if (cond == 1) return X; return 0;` form is what makes the image emit
 * `bnel` with the zero in the delay slot.
 
 */
int GAMEUTIL_is_player_obj(void);
extern char D_kernel_data_1934[];

int CheckSwordIndicateAimPoint(void) {
    if (GAMEUTIL_is_player_obj() == 1)
        return *(int *)(D_kernel_data_1934);
    return 0;
}
