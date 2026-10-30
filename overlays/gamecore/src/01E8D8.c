/* GAMECORE.XFF @ 0x01E8D8 (56 B) - addPlayerO2
 * Evidence: `.data+0xA54` is loaded, `add.s` with `$f12`, compared against
 * 0x42C80000 (100.0f) and 0.0f (`bc1t` / `bc1fl` with `mov.s` in the delay
 * slot) and stored back - the same clamp shape as `setPlayerO2`, which needs
 * the explicit three-way if/else-if/else.
 * UNCONFIRMED: the global field meaning.
 
 */
extern float D_kernel_data_0A54;

void addPlayerO2(float delta) {
    float v = D_kernel_data_0A54 + delta;
    float r;

    if (v > 100.0f)
        r = 100.0f;
    else if (v < 0.0f)
        r = 0.0f;
    else
        r = v;
    D_kernel_data_0A54 = r;
}
