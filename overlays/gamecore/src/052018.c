/* GAMECORE.XFF @ 0x052018 (24 B) - get_cur_type_expression
 * Evidence: a0 += 4, sibling j
 * UNCONFIRMED: none
 */
int GAMEUTIL_get_cur_status_status_manager(char *p);

int get_cur_type_expression(char *p) {
    return GAMEUTIL_get_cur_status_status_manager(p + 4);
}
