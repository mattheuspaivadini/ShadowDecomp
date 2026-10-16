/* asm/cod/0231A8.s -> func_001231A8 @ 0x001231A8 (0x60 bytes, 24 insns)
 *
 * One-shot CreateSema (func_00106FE0 = `addiu $v1,$zero,0x40; syscall 0`) for
 * the signed handle D_00135960. If the handle is already valid (>= 0) it
 * returns -1; otherwise it builds the 0x20-byte parameter block on the stack
 * (the matched 00FB88.c layout, with the option pointer in field 0x14), stores
 * and returns the new handle:
 *
 *   if (D_00135960 >= 0) return -1;      ; bgez + `addiu $v0,$zero,-1`
 *   buf[1] = 1;                          ; sw $v1,0x4($sp)
 *   buf[5] = (int)D_00138DF0;            ; sw $v0,0x14($sp)
 *   buf[2] = 0;                          ; sw $zero,0x8($sp) (jal delay slot)
 *   D_00135960 = func_00106FE0(buf);     ; sw $v0,%lo(D_00135960)($s0)
 *   if (D_00135960 < 0) return -1;       ; reload, bltz + -1 in its slot
 *   return D_00135960;                   ; second reload
 *
 * The handle is re-read after the store (three memory accesses), which a plain
 * scalar declaration would collapse into store + one load, so it is declared
 * volatile (the matched sibling 023208.c reads/writes it once each and needs no
 * qualifier). $s0 holds the `lui` half of D_00135960 across the call.
 * MATCH GUESS: cc=29 (the D_00135960 family is cc=29 - 023208.c is matched at
 * cc=29; 16-byte-spaced $s0/$ra frame, buffer at $sp+0..0x1F) */
extern volatile int D_00135960[];   /* .data 0x00135960, 4 bytes (lui/%lo) */
extern int D_00138DF0[];            /* the semaphore option table (lui/%lo) */

int CreateSema(void *args);

int func_001231A8(void) {
    int buf[8];

    if (D_00135960[0] >= 0)
        return -1;
    buf[1] = 1;
    buf[5] = (int)D_00138DF0;
    buf[2] = 0;
    D_00135960[0] = CreateSema(buf);
    if (D_00135960[0] < 0)
        return -1;
    return D_00135960[0];
}
