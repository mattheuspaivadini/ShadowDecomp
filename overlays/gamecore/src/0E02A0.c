/* GAMECORE.XFF @ 0x0E02A0 (52 B) - CAM_copy_camera_base_data
 * Evidence: six `ld`/`sd` pairs covering +0x00..+0x28.
 * UNCONFIRMED: struct field meanings and callee argument/return types
 
 */
void CAM_copy_camera_base_data(char *dst, char *src) {
    *(long long *)(dst + 0x00) = *(long long *)(src + 0x00);
    *(long long *)(dst + 0x08) = *(long long *)(src + 0x08);
    *(long long *)(dst + 0x10) = *(long long *)(src + 0x10);
    *(long long *)(dst + 0x18) = *(long long *)(src + 0x18);
    *(long long *)(dst + 0x20) = *(long long *)(src + 0x20);
    *(long long *)(dst + 0x28) = *(long long *)(src + 0x28);
}
