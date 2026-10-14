/* asm/cod/0184E8.s -> func_001184E8 @ 0x001184E8 (0x8C bytes, 35 insns)
 *
 * Bounds-checked string store into word slot a2 of the array a1:
 *
 *   rem = a0->f30 - a2 * 4;              ; $s2, computed before the test
 *   if (a3 == 0) return 0;               ; bnez $s1 / daddu $v0,$zero,$zero
 *   n = func_001290C4(a3) + 1;           ; strlen(a3) + 1  -> $s0
 *   if (n < 0 || rem < n) return -0x21F; ; bltz + slt + beqz
 *   func_00128FB0(&a1[a2], a3);          ; strcpy(dst, src) (0x114-byte helper)
 *   return n;                            ; daddu $v0,$s0
 *
 * a1 is an `int *` (the index scales by 4 via `sll $s3,$a2,2`, held in $s3
 * across the strlen call, and `addu $a0,$s4,$s3`); a0 is only read at +0x30.
 * func_00128FB0 is the 128-bit strcpy (asm/cod/028FB0.s, returns $a3).
 * MATCH GUESS: cc=29 (0x00118xxx block: 018358/018578/0188E0 are cc=29 TUs;
 * 16-byte-stride $s0..$s4 saves) */
struct S0184E8 {
    char pad[0x30];
    int  f30;      /* 0x30 */
};

int  func_001290C4(char *s);
void func_00128FB0(void *dst, void *src);

int func_001184E8(struct S0184E8 *a0, int *a1, int a2, char *a3) {
    int rem;
    int n;

    rem = a0->f30 - a2 * 4;
    if (a3 == 0)
        return 0;
    n = func_001290C4(a3) + 1;
    if (n < 0 || rem < n)
        return -0x21F;
    func_00128FB0(&a1[a2], a3);
    return n;
}
