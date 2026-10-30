/* GAMECORE.XFF @ 0x0E04F0 (24 B) - CAM_destructor_target
 * Evidence: ops ld sd; calls j GAMEUTIL_destructor_record_info; frame
 * UNCONFIRMED: field names/types guessed from offsets
 */
void GAMEUTIL_destructor_record_info(char *p);
void CAM_destructor_target(char *p) {
    GAMEUTIL_destructor_record_info(p + 0x2CC);
}
