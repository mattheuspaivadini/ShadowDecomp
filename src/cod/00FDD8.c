/* asm/cod/00FDD8.s -> func_0010FDD8 @ 0x0010FDD8 (0x54 bytes, 21 insns)
 *
 * Timer subsystem start-up: eight plain calls, then a tail call to
 * func_00111AF0 (`ld $ra,0x0($sp); j func_00111AF0; addiu $sp,$sp,0x10`).
 * The only argument ever set up is the 0x2 for the 4th call
 * (func_00110430, the Timer 2 MODE programmer of the 010640/0110430 cluster).
 * Every `jal` keeps a `nop` delay slot (the pinned -g2 shape).
 *
 * The last call is a sibling call with a real frame restored in the `j` delay
 * slot - the framed family shape (0288E8/0289D0 in the manifest), i.e. cc=296.
 * MATCH GUESS: cc=296 (framed tail call)
 */
void func_0010FB88(void);
void func_0010FCC8(void);
void func_001102B8(void);
void func_00110430(int a0);
void func_00110670(void);
void func_00107768(void);
void func_0010FF00(void);
void func_0010F3C8(void);
void func_00111AF0(void);

void func_0010FDD8(void) {
    func_0010FB88();
    func_0010FCC8();
    func_001102B8();
    func_00110430(2);
    func_00110670();
    func_00107768();
    func_0010FF00();
    func_0010F3C8();
    func_00111AF0();
}
