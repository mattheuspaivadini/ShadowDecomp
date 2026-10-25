/* KERNEL.XFF @ 0x006790 (24 B) - iosiWakeupThread
 * Evidence: frame + sibling `j iWakeupThread` with $a0 = word +4 of the argument.
 * UNCONFIRMED: the argument type (a struct whose second word is a thread id).
 */
int iWakeupThread(int thid);
void iosiWakeupThread(int *p) { iWakeupThread(p[1]); }
