/* asm/cod/022458.s -> func_00122458 @ 0x00122458 (0x64 bytes, 25 insns)
 *
 *   func_001221D0();                             ; id / clear the command block
 *   func_00128FB0(D_00167F00 + 0x10, a0);        ; copy a0 into the record
 *   *(int *)(D_00167F00 + 8) = a1;
 *   return func_00123260(D_00167EC0, D_00167F00, 0);
 *
 * The D_00167F00 address is materialised once into $s0 (lui/addiu) and the +8
 * word store sits in the `jal func_00123260` delay slot; $s1 keeps a0 and $s2
 * keeps a1 across the first two calls ($s2 is set before the frame is even
 * complete).  The 0x40 frame saves $s0/$s1/$s2/$ra 0x10 apart (the 2.9 slot
 * layout) and the last call is a framed `jal` + epilogue, i.e. cc=29 (no
 * sibling-call optimisation).  Same 022DA0 "command" family idiom as the
 * matched 022BD8.
 * MATCH GUESS: cc=29
 * The `+0x10` offset is a named local (the const-local pattern of 022BD8).
 * RESIDUAL: none known; if the store lands before the lui it needs the
 * 022DA0 store-order variant. */
int sceNetcnfifInit(void);
void func_00128FB0(char *dst, char *src);
int sce_call_rpc(char *dst, char *src, int n);

extern char D_00167F00[];
extern char D_00167EC0[];

int sceNetcnfifGetCount(int a0, int a1) {
    int lit_0 = 0x10;

    sceNetcnfifInit();
    func_00128FB0(D_00167F00 + lit_0, (char *)a0);
    *(int *)(D_00167F00 + 8) = a1;
    return sce_call_rpc(D_00167EC0, D_00167F00, 0);
}
