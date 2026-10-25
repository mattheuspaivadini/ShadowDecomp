/* KERNEL.XFF @ 0x009E00 (40 B) - GetSymbolByIndex
 * Evidence: object->+0x1C header; symbol table base = header+0x28, index bias =
 * header+0x40, string/value base = header+0x2C; returns base + table[(index +
 * bias) * 16].word0. UNCONFIRMED: struct layout and field names (ELF-like
 * symbol table: 16-byte entries, st_name first).
 */
int GetSymbolByIndex(char *obj, int index) {
    char *h = *(char **)(obj + 0x1C);
    return *(int *)(h + 0x2C) + *(int *)(*(int *)(h + 0x28) + (index + *(int *)(h + 0x40)) * 16);
}
