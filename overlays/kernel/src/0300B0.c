/* KERNEL.XFF @ 0x0300B0 (256 B) - IirParam
 * Evidence: two float stores (0x30 = $f12, 0x2C = $f13) and `sw a1,0x0`
 * before `v1 = a1 - 1; sltiu v1,5` guards a 5-entry jump table at
 * .rodata+0x2F10 -> func_02FBD8 / func_02FD00 / func_02FEC8 / func_02F9D8 /
 * func_02FAD8 (all called with $a0 = p); every case branches to one tail that
 * divides p->0x10/0x14/0x18/0x08/0x0C by p->0x04 into p->0x34/0x38/0x3C/0x40/0x44
 * in ascending field order (the paired nops between `div.s` and `swc1` are the
 * FP-latency padding; the store order in the listing is the source order here).
 * UNCONFIRMED: struct/field names, the callee prototypes.
 */
typedef struct IirParam_s {
    int type;        /* 0x00 */
    float f04;       /* 0x04 */
    float f08;       /* 0x08 */
    float f0C;       /* 0x0C */
    float f10;       /* 0x10 */
    float f14;       /* 0x14 */
    float f18;       /* 0x18 */
    int pad[4];      /* 0x1C .. 0x2B */
    float f2C;       /* 0x2C */
    float f30;       /* 0x30 */
    float f34;       /* 0x34 */
    float f38;       /* 0x38 */
    float f3C;       /* 0x3C */
    float f40;       /* 0x40 */
    float f44;       /* 0x44 */
} IirParam_s;

void func_02FBD8(IirParam_s *p);
void func_02FD00(IirParam_s *p);
void func_02FEC8(IirParam_s *p);
void func_02F9D8(IirParam_s *p);
void func_02FAD8(IirParam_s *p);

void IirParam(IirParam_s *p, int type, float f12, float f13) {
    p->f30 = f12;
    p->f2C = f13;
    p->type = type;
    switch (type) {
    case 1:
        func_02FBD8(p);
        break;
    case 2:
        func_02FD00(p);
        break;
    case 3:
        func_02FEC8(p);
        break;
    case 4:
        func_02F9D8(p);
        break;
    case 5:
        func_02FAD8(p);
        break;
    }
    p->f34 = p->f10 / p->f04;
    p->f38 = p->f14 / p->f04;
    p->f3C = p->f18 / p->f04;
    p->f40 = p->f08 / p->f04;
    p->f44 = p->f0C / p->f04;
}
