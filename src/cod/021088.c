/* asm/cod/021088.s -> func_00121088 @ 0x00121088 (0x90 bytes, 36 insns)
 * Create the D_00138D68-backed semaphore and prime the D_00163CC8 table:
 *   D_00135940[0] = 0;
 *   buf[1] = 0x7F; buf[5] = (int)D_00138D68; buf[2] = 0;   (0x20-byte block)
 *   r = func_00106FE0(buf);          (CreateSema, syscall 0x40)
 *   D_00163CC0[0] = r;               (sw in the `bgez` delay slot)
 *   if (r < 0) return 0;
 *   fill 2 records (stride 0x24) of D_00163CC8 with {0, 0x200, 0x10, 0x4000}
 *   and return 1.
 * The fill loop is the matched 015008.c shape: plain `int` addresses (signed
 * `slt`) with the four constants materialised before the loop (LICM) and a
 * `do/while` (015008.s). The store order (D_00135940, buf[1], buf[5], buf[2])
 * follows the asm; buf is the 8-word frame (0x30 with $ra at 0x20).
 * MATCH GUESS: cc=29 (0231A8.c sibling CreateSema block, 015008.c loop) */
extern int D_00135940[];   /* .data 0x00135940, 4 bytes - array => lui/%lo */
extern int D_00138D68[];   /* semaphore option table (lui/%lo) */
extern int D_00163CC0[];   /* .bss 0x00163CC0, 8 bytes */
extern int D_00163CC8[];   /* .bss 0x00163CC8, 0x24-byte records */

int func_00106FE0(void *args);

int func_00121088(void) {
    int buf[8];
    int p;
    int end;
    int r;

    D_00135940[0] = 0;
    buf[1] = 0x7F;
    buf[5] = (int)D_00138D68;
    buf[2] = 0;
    r = func_00106FE0(buf);
    D_00163CC0[0] = r;
    if (r < 0)
        return 0;
    p = (int)D_00163CC8;
    end = (int)D_00163CC8 + 0x48;
    do {
        *(int *)(p + 0x0) = 0;
        *(int *)(p + 0x8) = 0x200;
        *(int *)(p + 0xC) = 0x10;
        *(int *)(p + 0x10) = 0x4000;
        p += 0x24;
    } while (p < end);
    return 1;
}
