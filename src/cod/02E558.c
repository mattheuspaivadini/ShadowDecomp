/* asm/cod/02E558.s -> func_0012E558 @ 0x0012E558
 * Tail-call trampoline (with a frame;
 * cc=296 keeps the frame). */
int _impure_ptr[];

void localeconv(void) {
    _localeconv_r(_impure_ptr[0]);
}
