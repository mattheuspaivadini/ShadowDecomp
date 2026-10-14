/* asm/cod/014BF8.s -> func_00114BF8 @ 0x00114BF8 (0x38 bytes, 12 insns)
 *
 * Pull a 0x14-byte record out of the .bss object D_0014B580 into the caller's
 * buffer and return the buffer (the getter twin of the env-put at the tail of
 * asm/cod/014A20.s, which copies the same 0x14 bytes the other way):
 *
 *   lui   $v1, %hi(D_0014B580)
 *   addiu $a4, $v1, %lo(D_0014B580)   ; src = &D_0014B580
 *   ldl/ldr $a1, 0x0($a4)             ; 8-byte piece 0
 *   ldl/ldr $a2, 0x8($a4)             ; 8-byte piece 8
 *   lw    $a3, 0x10($a4)              ; 4-byte tail
 *   sdl/sdr $a1, 0x0($a0)             ; ... same three pieces to $a0
 *   sdl/sdr $a2, 0x8($a0)
 *   sw    $a3, 0x10($a0)
 *   jr    $ra
 *    daddu $v0, $a0, $zero            ; return the destination
 *
 * The 8+8+4 chunking of a 0x14-byte copy is the block-move path with 8-byte
 * (MOVE_MAX_PIECES) pieces; the pieces use ldl/ldr/sdl/sdr - i.e. the copied
 * object is known to be only 4-byte aligned (a struct of plain words), NOT a
 * `long long` struct (that would emit ld/sd, compare the matched 012088.c /
 * 014020.c). Five unaligned 4-byte words would have given five lw/sw instead.
 * The word layout is the DMA-environment shape (stat/madr/qwc/taddr/chcr) but
 * the field identities stay UNCONFIRMED.
 * MATCH GUESS: cc=29 (the 0148xx-0150xx DMA range: 0148B8/0148E0/014918/015008)
 */
struct R14BF8 {
    unsigned int w00;   /* 0x00 */
    unsigned int w04;   /* 0x04 */
    unsigned int w08;   /* 0x08 */
    unsigned int w0C;   /* 0x0C */
    unsigned int w10;   /* 0x10 */
};

extern struct R14BF8 D_0014B580;

struct R14BF8 *func_00114BF8(struct R14BF8 *env) {
    *env = D_0014B580;
    return env;
}
