/* KERNEL.XFF @ 0x01BB78 (92 B) - decrement_letter_refcount
 * Evidence: when *pp is set: --**pp, iosFree(*pp) if it reached 0 (returns 1), and *pp = 0 on both paths (bnel slot); *pp is reloaded after the decrement (no type-based aliasing).
 */
void iosFree(void *p);

int decrement_letter_refcount(int **pref) {
    int freed = 0;

    if (*pref != 0) {
        (**pref)--;
        if (**pref == 0) {
            iosFree(*pref);
            freed = 1;
        }
        *pref = 0;
    }
    return freed;
}
