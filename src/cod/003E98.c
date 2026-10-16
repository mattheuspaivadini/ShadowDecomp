/* asm/cod/003E98.s -> func_00103E98 @ 0x00103E98 (0x8C bytes, 35 insns)
 *
 * Stage/loader helper: three variadic register-save calls (the 0x50-byte
 * `void f(int, int, ...)` stubs func_00105948/func_00105990, see the matched
 * 005948.c/005990.c) with the two mask words 0xFFFF00 and 0x40FFFF80 and a
 * stage pointer, then two spin loops on the poll helpers and a tail call:
 *
 *   func_00105948(0xFFFF00,  D_00136AE8);        ; lui 0x00FF | ori 0xFF00
 *   func_00105948(0x40FFFF80, D_0013A018, a0);   ; lui 0x40FF | ori 0xFF80
 *   func_00105990(0xFFFF00,  D_0013A020);
 *   while (func_0010F168(a0) == 0) ;             ; beqz -> loop
 *   while (func_0010F118() == 0) ;               ; beqz -> loop
 *   func_00105990(0xFFFF00,  D_0013A028);        ; sibling call `j`
 *
 * The argument is copied to $s0 at entry and re-used for the poll loop and the
 * third call's $a2; func_0010F168 dereferences it as a `char *` (it is a
 * string/format walker), so the parameter is a pointer.
 * The trailing func_00105990 is a bare `j` with the epilogue before it, i.e.
 * this TU does have sibling-call optimisation; the frame is 0x10 with an
 * 8-byte-spaced $s0/$ra pair, the 2.96 shape (0x00103xxx is a cc=296 block).
 * MATCH GUESS: cc=296 */
extern char D_00136AE8[];   /* lui/%lo */
extern char D_0013A018[];   /* lui/%lo */
extern char D_0013A020[];   /* lui/%lo */
extern char D_0013A028[];   /* lui/%lo */

void PutString(int a0, int a1, ...);
void PutStringS(int a0, int a1, ...);
int  sceSifRebootIop(char *s);
int  sceSifSyncIop(void);

void LoaderSysRebootIop(char *a0) {
    PutString(0xFFFF00, (int)D_00136AE8);
    PutString(0x40FFFF80, (int)D_0013A018, (int)a0);
    PutStringS(0xFFFF00, (int)D_0013A020);
    while (sceSifRebootIop(a0) == 0)
        ;
    while (sceSifSyncIop() == 0)
        ;
    PutStringS(0xFFFF00, (int)D_0013A028);
}
