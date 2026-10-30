/* GAMECORE.XFF @ 0x09A0F8 (60 B) - AI_GetRandomRange
 * Evidence: $f12 saved to $f21, $f13 to $f20, `sub.s f20,f20,f21` in the
 * `jal iosGetRandom` delay slot, then `mul.s` and `add.s $f0,$f21,$f20`.
 * UNCONFIRMED: none
 
 */
float iosGetRandom(void);

float AI_GetRandomRange(float min, float max) {
    return min + (max - min) * iosGetRandom();
}
