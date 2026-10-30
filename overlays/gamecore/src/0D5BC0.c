/* GAMECORE.XFF @ 0x0D5BC0 (44 B) - reset_camera_collision_data_except_slide_move_ratio
 * Evidence: four `sw $zero` at 0x0/0x4/0x8/0xC of the object, then a tail `j
 * ConstructorCollisionDynamics` with `$a0 = obj + 0x10`.
 * UNCONFIRMED: field meanings
 
 */
void ConstructorCollisionDynamics(void *p);

void reset_camera_collision_data_except_slide_move_ratio(void *p) {
    *(int *)((char *)p + 0x0) = 0;
    *(int *)((char *)p + 0x4) = 0;
    *(int *)((char *)p + 0x8) = 0;
    *(int *)((char *)p + 0xC) = 0;
    ConstructorCollisionDynamics((char *)p + 0x10);
}
