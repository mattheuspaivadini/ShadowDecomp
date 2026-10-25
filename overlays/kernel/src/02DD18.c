/* KERNEL.XFF @ 0x02DD18 (64 B) - Sg2VabInit
 * Evidence: the static at .text+0x2DC58 is called for ids 0..7; returns 0.
 */
int func_02DC58(int id);

int Sg2VabInit(void) {
    int i;

    for (i = 0; i < 8; i++) {
        func_02DC58(i);
    }
    return 0;
}
