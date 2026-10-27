/* KERNEL.XFF @ 0x009EE8 (64 B) - isysGetModuleObjMallocSize
 * Evidence: bit 30 of word +0x2C selects the block pointer (+0x1C directly, or
 * its word +4); the size is the low 24 bits of the word at that pointer - 4,
 * in 4-byte units (`sll 2`). UNCONFIRMED: layout and names.
 */
int isysGetModuleObjMallocSize(char *obj) {
    char *p;

    if (*(int *)(obj + 0x2C) & 0x40000000) {
        p = (char *)*(int *)(*(char **)(obj + 0x1C) + 4) - 4;
    } else {
        p = *(char **)(obj + 0x1C) - 4;
    }
    return (**(unsigned int **)p & 0xFFFFFF) << 2;
}
