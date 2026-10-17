/* asm/cod/0224C0.s -> sceNetcnfifGetList.
 * const_local_0x10_0: 0x10 materialised into a named local before the loop (Session 20)
 * MATCHED. */
/* asm/cod/0224C0.s -> func_001224C0 @ 0x001224C0 (0x8C bytes, 35 insns)
 * Transfer-family entry (022D68/022DA0/022E18): func_001221D0() resets the
 * D_00167F00 tracking block, the caller's buffer is copied into it at +0x10,
 * three words are stored (0x0 = a3, 0x8 = a1, 0xC = a2) and the block is handed
 * to func_00123260(D_00167EC0, D_00167F00, 1) whose result is returned.
 * `jal` + real epilogue (no tail `j`) and a filled `jal` shadow, i.e. no
 * sibling-call folding - the cc=29 form (cf. the matched 022E18.c).
 * MATCH GUESS: cc=29 */
int sceNetcnfifInit(void);
void func_00128FB0(char *dst, char *src);
int sce_call_rpc(char *dst, char *src, int n);

extern int D_00167F00[];
extern char D_00167EC0[];

int sceNetcnfifGetList(int a0, int a1, int a2, int a3) {int lit_0 = 0x10;

    sceNetcnfifInit();
    func_00128FB0((char *)D_00167F00 + lit_0, (char *)a0);
    D_00167F00[0] = a3;
    D_00167F00[2] = a1;
    D_00167F00[3] = a2;
    return sce_call_rpc(D_00167EC0, (char *)D_00167F00, 1);
}
