/* KERNEL.XFF @ 0x02CCC8 (400 B) - func_02CCC8 (static, no symbol in the shipped .symtab)
 * Evidence: byte-stream command parser: takes two bytes through the pointer field at
 * +0x60 (each post-increment stored back, so the address of the field is kept in a
 * register), then `switch (a)`: 0x63 -> nested `switch (b)` (0x14 copies +0x68 into
 * +0x69 and the stream pointer into +0x6C, 0x1E rewinds +0x68/+0x60 from +0x69/+0x6C
 * when the repeat counter +0x70 is not 0x7F and decrements it, default sets the
 * fall-through flag); 0x5A -> calls the callback kept at .bss+0x9AC88 with
 * (.bss+0x9AC80 byte, +0x68 & 0xF, second byte); 0x66 -> +0x70 = second byte.
 * Unhandled commands are appended to .bss+0x9AC90 (index .bss+0x9B490), first
 * recording a changed +0x68 in that buffer and in .bss+0x9B494. The two nested
 * switches (not an if/else chain) are what produce the beq/beql compare order.
 * UNCONFIRMED: function name, struct/field names, the callback prototype.
 */
struct Sg2Rx {
    char pad00[0x60];
    unsigned char *ptr;   /* 0x60 */
    char pad64[4];
    unsigned char b68;    /* 0x68 */
    unsigned char b69;    /* 0x69 */
    char pad6A[2];
    unsigned int saved;   /* 0x6C */
    int rep;              /* 0x70 */
};
extern unsigned char D_kernel_bss_9AC90[];
extern void (*D_kernel_bss_9AC88)(int, int, int);
extern unsigned char D_kernel_bss_9AC80;
extern unsigned int D_kernel_bss_9B494;
extern int D_kernel_bss_9B490;

void func_02CCC8(struct Sg2Rx *p) {
    unsigned char a;
    unsigned char b;
    int v;
    unsigned char c;
    int flag = 0;

    a = *p->ptr++;
    b = *p->ptr++;

    switch (a) {
    case 0x63:
        switch (b) {
        case 0x14:
            p->b69 = p->b68;
            p->saved = (unsigned int)p->ptr;
            break;
        case 0x1E:
            v = p->rep;
            if (v != 0x7F) {
                p->rep = v - 1;
                v = v - 1;
            }
            if (v > 0) {
                p->b68 = p->b69;
                p->ptr = (unsigned char *)p->saved;
            }
            break;
        default:
            flag = 1;
            break;
        }
        break;
    case 0x5A:
        if (D_kernel_bss_9AC88 != 0) {
            D_kernel_bss_9AC88(D_kernel_bss_9AC80, p->b68 & 0xF, b);
        }
        break;
    case 0x66:
        p->rep = b;
        break;
    default:
        flag = 1;
        break;
    }
    if (flag) {
        c = p->b68;
        if (D_kernel_bss_9B494 != c) {
            D_kernel_bss_9B494 = c;
            D_kernel_bss_9AC90[D_kernel_bss_9B490++] = c;
        }
        D_kernel_bss_9AC90[D_kernel_bss_9B490++] = a;
        D_kernel_bss_9AC90[D_kernel_bss_9B490++] = b;
    }
}
