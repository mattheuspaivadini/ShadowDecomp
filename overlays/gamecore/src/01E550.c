/* GAMECORE.XFF @ 0x01E550 (64 B) - getPlayerHpRatio
 * Evidence: `jal func_01E3E0` (result parked in `$f20` via the second call's
 * delay slot), `jal func_01E590`, then `div.s $f20,$f20,$f0`, `$f0 = 0x42C8`
 * (100.0f) and `mul.s $f0,$f20,$f0`.
 * UNCONFIRMED: the two callees' roles (current vs maximum HP).
 
 */
float func_01E3E0(void);
float func_01E590(void);

float getPlayerHpRatio(void) {
    float current = func_01E3E0();
    float maximum = func_01E590();

    return current / maximum * 100.0f;
}
