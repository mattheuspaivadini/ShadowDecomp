/* MATCHED (Session 6): byte-exact with the 2.9-ee-991111-01 revision (cc=29)
 * when the record is addressed through a `struct R020D10 *r = &D[index];`
 * local, which is what makes ee-gcc add 0xD0 to the record base ($a0) instead
 * of to the array base ($v0). Session 4 recorded this as an unfixable
 * `+0xD0` ordering difference under ee-gcc2.96.
 *
 * asm/cod/020D10.s -> func_00120D10 @ 0x00120D10 (0x48 bytes) */
struct R020D10 {
    char pad00[0xD0];
    int  keys[32];
    char pad150[0x34];
};

extern struct R020D10 D_00135638[];

int func_00120D10(int index, int key) {
    struct R020D10 *r = &D_00135638[index];
    int i;

    for (i = 0; i < 32; i++) {
        if (r->keys[i] == key)
            return 1;
    }
    return 0;
}
