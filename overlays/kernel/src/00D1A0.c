/* KERNEL.XFF @ 0x00D1A0 (332 B) - iosDumpMatrix
 * Evidence: copies both labels to 256-byte stack buffers, blanks every isgraph character (Newlib _ctype_ & (_P|_U|_L|_N)) so the continuation rows are indented, then prints the four rows with iosDumpFVector (row 0 with the real first label, row 3 with the real second label). UNCONFIRMED: names.
 */
extern char _ctype_[];
unsigned int strlen(const char *s);
char *strcpy(char *d, const char *s);
void iosDumpFVector(char *name, void *arg, char *name2, float *v);

#define isgraph(c) ((_ctype_ + 1)[(int)(c)] & 0x17)

void iosDumpMatrix(char *name, void *arg, char *name2, float (*m)[4]) {
    char a[256];
    char b[256];
    int la;
    int lb;
    int i;

    la = strlen(name);
    lb = strlen(name2);
    strcpy(a, name);
    strcpy(b, name2);
    for (i = 0; i < la; i++) {
        if (isgraph(a[i])) {
            a[i] = ' ';
        }
    }
    for (i = 0; i < lb; i++) {
        if (isgraph(b[i])) {
            b[i] = ' ';
        }
    }
    for (i = 0; i < 4; i++) {
        iosDumpFVector(i == 0 ? name : a, arg, i == 3 ? name2 : b, m[i]);
    }
}
