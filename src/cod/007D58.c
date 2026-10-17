/* asm/cod/007D58.s -> func_00107D58.
 * SIO putc: '\n' -> CR LF; void prototypes give the cc=29 framed tail j (Session 19)
 * MATCHED. */
/* UNCONFIRMED: void return types are inferred from the framed tail `j`
 * (cc=29 emits it only for void calls); 007C70 itself returns its argument. */
void func_00107C70(int value);

void func_00107D58(int c) {
    if (c == '\n') {
        func_00107C70('\r');
        func_00107C70('\n');
        return;
    }
    func_00107C70(c);
}
