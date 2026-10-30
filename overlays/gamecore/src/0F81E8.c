/* GAMECORE.XFF @ 0x0F81E8 (36 B) - setAttainRangeStruct
 * Evidence: stores $v0, 0x3E0($a0), $v1, 0x3E8($a0), $v0, 0x3F0($a0), $v1, 0x3F8($a0); loads $v0, 0x0($a1), $v1, 0x8($a1), $v0, 0x10($a1), $v1, 0x18($a1); frame
 
 */
/* UNCONFIRMED: copies a 0x20-byte range struct into +0x3E0. */
typedef struct {
    long long a, b, c, d;
} AttainRange;

void setAttainRangeStruct(char *p, AttainRange *src) {
    *(AttainRange *)(p + 0x3E0) = *src;
}
