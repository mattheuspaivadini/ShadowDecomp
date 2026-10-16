/* asm/cod/006430.s -> func_00106430 @ 0x00106430 (0x64 bytes, 25 insns)
 *
 * Fill the 40-row x 60-column table of 8-byte records at D_0013ED90 (.bss)
 * with the single template record D_0013A160 (gp-relative small data, the
 * 8-byte record shape of the matched 006B58 sibling):
 *
 *   a3 = &D_0013ED90;  a2 = &D_0013A160;  i = 0;
 *   do {
 *       v0 = (i*15) << 5 + a3          ; row byte offset: i*60 records*8 B,
 *                                      ; ee-gcc folds i*60 into (i*15)<<2 and
 *                                      ; combines it with the *8 into <<5
 *       for (j = 0x3B; j >= 0; j--) {  ; 60 records (insert_bct countdown)
 *           ldl/ldr $a4, 0x0($a2)      ; one 8-byte 4-aligned block move
 *           sdl/sdr $a4, 0x0($v0)      ; (BLKmode record copy)
 *           v0 += 8;
 *       }
 *       i++;
 *   } while (i < 0x28);
 *
 * The source record is re-loaded every iteration (a load cannot be hoisted out
 * of a loop that stores, in ee-gcc), and the outer induction variable is the
 * *index* i*15 (`addiu $a0,$a0,0xF`), not the byte offset.
 * MATCH GUESS: cc=296 (default revision, like the matched 006B58 sibling)
 */
struct E006430 {
    int           field00;   /* 0x00 */
    unsigned char field04;   /* 0x04 */
    char          pad05[3];  /* to 0x08 */
};

extern struct E006430 D_0013A160;     /* .sdata, gp-relative: template record  */
extern struct E006430 D_0013ED90[];   /* .bss: 40 rows x 60 records            */

void ClearDisplay(void) {
    int i;
    int j;

    for (i = 0; i < 0x28; i++)
        for (j = 0; j < 0x3C; j++)
            D_0013ED90[i * 0x3C + j] = D_0013A160;
}
