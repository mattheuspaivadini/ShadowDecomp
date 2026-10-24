/* KERNEL.XFF @ 0x01ABA8 (8 B) - isysSetObjImmediateDeleteFunc
 * Evidence: `jr $ra` with `sw $a1,0x18($a0)` in the delay slot: stores the
 * second argument into the object at +0x18 (UNCONFIRMED field name).
 */
void isysSetObjImmediateDeleteFunc(unsigned char *obj, int fn) {
    *(int *)(obj + 0x18) = fn;
}
