/* GAMECORE.XFF @ 0x0704F0 (40 B) - end_nico_sight_on
 * Evidence: `$a0 -> $v0`, three zero word stores at +0/+4/+8, `$a0 = $v0+0xC`,
 * then a sibling `j` to `end_nico_yaw_pitch_cntrl`.
 * UNCONFIRMED: the three cleared fields' meanings and the callee prototype.
 
 */
void end_nico_yaw_pitch_cntrl(void *ctrl);

void end_nico_sight_on(char *work) {
    *(int *)(work + 0x0) = 0;
    *(int *)(work + 0x4) = 0;
    *(int *)(work + 0x8) = 0;
    end_nico_yaw_pitch_cntrl(work + 0xC);
}
