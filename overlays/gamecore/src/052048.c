/* GAMECORE.XFF @ 0x052048 (24 B) - GAMEUTIL_get_cur_interp_ratio_expression
 * Evidence: a0 += 0x14, sibling j
 * UNCONFIRMED: return type float?
 */
float GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(char *p);

float GAMEUTIL_get_cur_interp_ratio_expression(char *p) {
    return GAMEUTIL_get_interp_ratio_interp_ratio_cntrl(p + 0x14);
}
