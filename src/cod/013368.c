/* asm/cod/013368.s -> sceVif1PkAddGsData.
 * sceVif1PkAddGsData (SHN_ABS)
 * MATCHED (Session 12). */
int *sceVif1PkAddGsData(int **pp, long long v) {
    int *p = *pp;

    *p++ = (int)v;
    *p = (int)(v >> 32);
    *pp = p + 1;
    return p;
}
