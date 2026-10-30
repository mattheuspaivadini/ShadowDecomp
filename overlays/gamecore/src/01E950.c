/* GAMECORE.XFF @ 0x01E950 (60 B) - getNowPower
 * Evidence: `jal _gameFWorkChk` with `$a0 = 0xC`, `div.s $f0,100.0f`
 * (0x42C80000), then `.bss+0x4AE8` loaded and multiplied by the quotient.
 * UNCONFIRMED: the `.bss` power-scale name.
 
 */
extern char D_kernel_bss_0000[];
float _gameFWorkChk(int id);

float getNowPower(void) {
    float ratio = _gameFWorkChk(0xC) / 100.0f;

    return *(float *)(D_kernel_bss_0000 + 0x4AE8) * ratio;
}
