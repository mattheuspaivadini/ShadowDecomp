/* GAMECORE.XFF @ 0x052030 (24 B) - get_pre_type_expression
 * Evidence: a0 += 4, sibling j
 * UNCONFIRMED: none
 */
int GAMEUTIL_get_pre_changed_status_status_manager(char *p);

int get_pre_type_expression(char *p) {
    return GAMEUTIL_get_pre_changed_status_status_manager(p + 4);
}
