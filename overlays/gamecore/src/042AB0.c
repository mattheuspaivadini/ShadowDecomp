/* GAMECORE.XFF @ 0x042AB0 (52 B) - SCRGetRoot
 * Evidence: `$a0` saved in `$s0`, `$a0 = $a1` in the `jal GetLayoutClass`
 * delay slot, then `lw $v1,0x134($v0)`, `lq`/`sq` of one 128-bit value.
 * UNCONFIRMED: the layout field meaning and the callee prototype.
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

struct LayoutClass {
    char pad[0x134];
    u_long128 *root;
};

struct LayoutClass *GetLayoutClass(int obj);

void SCRGetRoot(void *out, int obj) {
    *(u_long128 *)out = *GetLayoutClass(obj)->root;
}
