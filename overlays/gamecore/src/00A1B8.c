/* GAMECORE.XFF @ 0x00A1B8 (28 B) - GAMEUTIL_constructor_col_plane_info_filter
 * Evidence: frame 0x10, forwards obj in $a0, sets float args $f12 = 0.0f,
 * $f13 = 0.0f, and tail-calls GAMEUTIL_init_col_plane_info_filter.
 */
void GAMEUTIL_init_col_plane_info_filter(void *obj, float f12, float f13);

void GAMEUTIL_constructor_col_plane_info_filter(void *obj) {
    GAMEUTIL_init_col_plane_info_filter(obj, 0.0f, 0.0f);
}
