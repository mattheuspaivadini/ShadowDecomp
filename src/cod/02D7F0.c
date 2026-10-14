/* asm/cod/02D7F0.s -> func_0012D7F0 @ 0x0012D7F0 (0x5C bytes)
 *   lui   $v0, %hi(func_0012FA40)   ... four function pointers ...
 *   sw    $a3, 0x54($a0)           ; p->field54 = a3
 *   sh    $a1, 0xC($a0)            ; p->field0C = a1
 *   sh    $a2, 0xE($a0)            ; p->field0E = a2
 *   sw    $v0, 0x20($a0)           ; p->field20 = &func_0012FA40
 *   sw    $v1, 0x24($a0)
 *   sw    $a4, 0x28($a0)
 *   sw    $a5, 0x2C($a0)
 *   sw    $zero, 0x0/0x4/0x8/0x10/0x14/0x18($a0)
 *   jr    $ra
 *    sw   $a0, 0x1C($a0)           ; p->field1C = p
 *
 * Initialise a handler struct: zero the fields, install two shorts, four
 * function pointers and the extra argument.
 */
struct S02D7F0 {
    int   field00;   /* 0x00 */
    int   field04;   /* 0x04 */
    int   field08;   /* 0x08 */
    short field0C;   /* 0x0C */
    short field0E;   /* 0x0E */
    int   field10;   /* 0x10 */
    int   field14;   /* 0x14 */
    int   field18;   /* 0x18 */
    int   field1C;   /* 0x1C */
    int   field20;   /* 0x20 */
    int   field24;   /* 0x24 */
    int   field28;   /* 0x28 */
    int   field2C;   /* 0x2C */
    char  pad30[0x24];
    int   field54;   /* 0x54 */
};

extern void func_0012FA40(void);
extern void func_0012FAA8(void);
extern void func_0012FB28(void);
extern void func_0012FB90(void);

void func_0012D7F0(struct S02D7F0 *p, short a1, short a2, int a3) {
    p->field00 = 0;
    p->field04 = 0;
    p->field08 = 0;
    p->field0C = a1;
    p->field0E = a2;
    p->field10 = 0;
    p->field14 = 0;
    p->field18 = 0;
    p->field1C = (int)p;
    p->field20 = (int)func_0012FA40;
    p->field24 = (int)func_0012FAA8;
    p->field28 = (int)func_0012FB28;
    p->field2C = (int)func_0012FB90;
    p->field54 = a3;
}
