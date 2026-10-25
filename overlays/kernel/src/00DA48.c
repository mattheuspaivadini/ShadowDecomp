/* KERNEL.XFF @ 0x00DA48 (72 B) - iosFvecToICol
 * Evidence: iosFTOI0Vector(tmp, v) into a 4-int stack buffer, then the low byte of each int is stored to col[0..3] (lbu/sb).
 */
void iosFTOI0Vector(int *d, float *s);

void iosFvecToICol(unsigned char *col, float *v) {
    int t[4];

    iosFTOI0Vector(t, v);
    col[0] = t[0];
    col[1] = t[1];
    col[2] = t[2];
    col[3] = t[3];
}
