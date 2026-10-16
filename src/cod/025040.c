/* asm/cod/025040.s -> func_00125040 @ 0x00125040 (0x3C bytes, 15 insns)
 * Decompose the float argument ($f12 is stored to its home slot sp+0x10, whose
 * address goes in $a0) with func_00127048(float *, int *) into the 4-word stack
 * buffer at sp+0x0, then forward the words to func_00125870(a0, a1, a2, a3:64).
 * The 64-bit 4th argument is `lwu $a3, 0xC($sp); dsll $a3, $a3, 30`, i.e.
 * (unsigned long long)buf[3] << 30 - the zero-extending `lwu` means the buffer
 * element is unsigned.
 * MATCH GUESS: cc=296 (0x1258xx/0x1259xx family is 2.96-only) */
extern int __unpack_f(float *f, unsigned int *out);
extern int __make_dp(int a0, int a1, int a2, long long a3);

int fptodp(float f) {
    unsigned int buf[4];

    __unpack_f(&f, buf);
    return __make_dp(buf[0], buf[1], buf[2], (unsigned long long)buf[3] << 30);
}
