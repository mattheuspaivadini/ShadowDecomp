/* GAMECORE.XFF @ 0x01E8A8 (48 B) - setPlayerO2
 * Evidence: `c.lt.s` against 0x42C80000 (100.0f) then against 0.0f, the
 * second compare uses `bc1fl` with `mov.s $f0,$f12` in the delay slot, and the
 * clamped value is stored to `.data+0xA54`.
 * UNCONFIRMED: the global field meaning.
 
 */
extern float D_kernel_data_0A54;

void setPlayerO2(float value) {
    float v;

    if (value > 100.0f)
        v = 100.0f;
    else if (value < 0.0f)
        v = 0.0f;
    else
        v = value;

    D_kernel_data_0A54 = v;
}
