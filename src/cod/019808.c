/* func_00119808 @ 0x00119808 (0x34 bytes): dispatch on bit 1 of the sixth
 * argument. */
int func_00119670(int a0, int a1, int a2, int a3, int a4);
int func_00119708(int a0, int a1, int a2, int a3, int a4);

int func_00119808(int a0, int a1, int a2, int a3, int a4, int a5) {
    if (a5 & 2)
        return func_00119670(a0, a1, a2, a3, a4);
    return func_00119708(a0, a1, a2, a3, a4);
}
