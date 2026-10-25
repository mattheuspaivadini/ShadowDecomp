/* KERNEL.XFF @ 0x01B900 (64 B) - isysGetLetterObj
 * Evidence: switch on byte +8 (6..22, jump table at .rodata+0x2530): types 6, 9, 11, 13 and 22 return the object, everything else NULL (table read from the container). UNCONFIRMED: type names.
 */
struct IsysObj {
    char pad[8];
    unsigned char type;
};

struct IsysObj *isysGetLetterObj(struct IsysObj *obj) {
    switch (obj->type) {
    case 6:
    case 9:
    case 11:
    case 13:
    case 22:
        return obj;
    }
    return 0;
}
