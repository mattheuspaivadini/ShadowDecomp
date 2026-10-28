/* KERNEL.XFF @ 0x02B8B8 (20 B) - func_02B8B8 (static, no symbol in the shipped .symtab)
 * Evidence: advances the SMF track pointer (+0x60) by 8 bytes and returns 0 (chunk header skip). UNCONFIRMED: names.
 */
struct Sg2SmfTrack {
    char pad[0x60];
    unsigned char *ptr;
};

int func_02B8B8(struct Sg2SmfTrack *t) {
    t->ptr += 8;
    return 0;
}
