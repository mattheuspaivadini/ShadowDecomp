/* asm/cod/0211B8.s -> func_001211B8 @ 0x001211B8 (0x40 bytes, 14 insns)
 *
 * Store a 16-byte sub-block into record `index` of the 0x24-byte table
 * D_00163CC8 and report success:
 *
 *   addiu $v0, $zero, 0x24            ; record stride
 *   lui   $v1, %hi(D_00163CC8)
 *   mult  $a0, $a0, $v0               ; index * 0x24 (R5900 3-operand mult)
 *   addiu $v1, $v1, %lo(D_00163CC8)
 *   addu  $a0, $a0, $v1               ; &D_00163CC8[index]
 *   ldl/ldr $v1, 0x0($a1)             ; 8 bytes from the caller's block
 *   ldl/ldr $a2, 0x8($a1)
 *   sdl/sdr $v1, 0x8($a0)             ; -> record + 0x08 (block field)
 *   sdl/sdr $a2, 0x10($a0)
 *   jr    $ra
 *    addiu $v0, $zero, 0x1            ; return 1
 *
 * The 8+8 chunking of a 16-byte copy is the block-move path with 8-byte
 * (MOVE_MAX_PIECES) pieces and the ldl/ldr/sdl/sdr pair means both sides are
 * only known to be 4-byte aligned: a struct of plain words (a `long long`
 * struct would emit ld/sd - see the matched 012088.c/014020.c). The `mult
 * $a0,$a0,0x24` for the literal stride is the 2.9-generation (cc=29) shape,
 * as in the matched 021E88/0220B0/022018/0220F8 siblings, which also index
 * D_00163CC8 with this same 0x24 stride.
 * MATCH GUESS: cc=29
 */
struct B0211B8 {                /* 16-byte block stored at record + 0x08 */
    unsigned int w0;            /* 0x00 */
    unsigned int w4;            /* 0x04 */
    unsigned int w8;            /* 0x08 */
    unsigned int wC;            /* 0x0C */
};

struct R0211B8 {                /* 0x24-byte record */
    unsigned int    w00;        /* 0x00 */
    unsigned int    w04;        /* 0x04 */
    struct B0211B8  blk;        /* 0x08 */
    unsigned int    w18;        /* 0x18 */
    unsigned int    w1C;        /* 0x1C */
    unsigned int    w20;        /* 0x20 */
};

extern struct R0211B8 D_00163CC8[];

int func_001211B8(int index, struct B0211B8 *src) {
    D_00163CC8[index].blk = *src;
    return 1;
}
