/* GAMECORE.XFF @ 0x0C56F8 (28 B) - timeAttackTimeScriptEnd
 * Evidence: ops lw lwc1 sw; data <.data>+0x1940
 * UNCONFIRMED: field names/types guessed from offsets
 */
extern struct { int a, b, c, flags; float d, limit, timer; } D_kernel_data_1940;

float timeAttackTimeScriptEnd(void) {
    D_kernel_data_1940.flags |= 0x20;
    return D_kernel_data_1940.timer;
}
