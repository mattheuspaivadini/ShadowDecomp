/* GAMECORE.XFF @ 0x051F80 (28 B) - update_type_expression
 * Evidence: a0 += 4, a2 = 0, sibling j GAMEUTIL_doit_status_manager
 * UNCONFIRMED: none
 */
int GAMEUTIL_doit_status_manager(char *p, int a, int b);

int update_type_expression(char *p, int a) {
    return GAMEUTIL_doit_status_manager(p + 4, a, 0);
}
