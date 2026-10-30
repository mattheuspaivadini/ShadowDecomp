/* KERNEL.XFF @ 0x000BB8 (216 B) - iosGetSecondFromTCount
 * Evidence: one `__udivdi3` by 150000000 (0x08F0D180, loaded with lui/ori)
 * followed by a shift/add expansion of `sec * 150000000` and `dsubu` = the
 * remainder is written as `count - sec * 150000000` (a `%` would emit a second
 * `__umoddi3` call); both halves are converted with the unsigned-64 `__floatdisf`
 * + `add.s f,f` doubling idiom (`bltz` on the 64-bit value), so the argument and
 * locals are `unsigned long long`; result = seconds + rest * 6.6666667e-9f
 * (0x31E5109E in the image; every literal spelling of 1/150000000 compiles to
 * that word with this compiler).
 * UNCONFIRMED: parameter name/unit.
 */
typedef unsigned long long u_long;

float __floatdisf(long long v);
u_long __udivdi3(u_long a, u_long b);

float iosGetSecondFromTCount(u_long count) {
    u_long sec = count / 150000000;
    u_long rem = count - sec * 150000000;

    return (float)sec + (float)rem * 6.6666667e-9f;
}
