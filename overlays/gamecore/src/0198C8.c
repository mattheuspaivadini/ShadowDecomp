/* GAMECORE.XFF @ 0x0198C8 (56 B) - gStatGetPlayerAccessoriesDamgeRaitoToPlayer
 * Evidence: `$f0 = 1.0f`, `bnel` on the `.data+0x9DC` pointer with
 * `lwc1 $f0,0x8($v0)` in the delay slot, then a `beqz` on the `.data+0x9E0`
 * pointer whose delay slot moves the running value to `$f1`, `mul.s` by
 * `0x8($v0)` and `mov.s $f0,$f1` in the return slot - the shape of a ternary
 * returning either the product or the running value.
 * UNCONFIRMED: the two pointer fields' meaning.
 
 */
struct AccessoryStat {
    char pad[8];
    float ratio;
};

extern struct AccessoryStat *D_kernel_data_09DC;
extern struct AccessoryStat *D_kernel_data_09E0;

float gStatGetPlayerAccessoriesDamgeRaitoToPlayer(void) {
    float ratio = 1.0f;

    if (D_kernel_data_09DC != 0)
        ratio = D_kernel_data_09DC->ratio;
    return D_kernel_data_09E0 != 0 ? ratio * D_kernel_data_09E0->ratio : ratio;
}
