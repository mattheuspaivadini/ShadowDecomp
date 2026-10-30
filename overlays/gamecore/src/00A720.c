/* GAMECORE.XFF @ 0x00A720 (56 B) - GAMEUTIL_get_data_record_info
 * Evidence: `bltz $a1` and a separate `slt $a1,0xC($a0)` + `beqz` guard the
 * lookup, then `mult $v0,$a1,0x0($a0)` (stride) added to `0x8($a0)` (base);
 * both failure edges land on one trailing `jr`/`daddu $v0,$zero` block, so the
 * source is a `&&` guard with a single `return 0` after it (two separate
 * `return 0` statements merge into the success epilogue).
 * UNCONFIRMED: the record struct field meanings.
 
 */
struct DataRecordTable {
    int stride;
    char pad[4];
    void *base;
    int count;
};

void *GAMEUTIL_get_data_record_info(struct DataRecordTable *table, int index) {
    if (index >= 0 && index < table->count)
        return (char *)table->base + index * table->stride;
    return 0;
}
