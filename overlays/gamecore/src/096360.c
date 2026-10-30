/* GAMECORE.XFF @ 0x096360 (36 B) - AddDefaultAIGroup
 * Evidence: `lui 0x1 / addiu 0x7D48` of <.bss> into $a1, $a2/$a3 zeroed, tail
 * `j isysAddGroupWithLinkParam`.
 * UNCONFIRMED: none
 
 */
extern char D_kernel_bss_17D48[];
void isysAddGroupWithLinkParam(int a0, void *link, int a2, int a3);

void AddDefaultAIGroup(int a0) {
    isysAddGroupWithLinkParam(a0, D_kernel_bss_17D48, 0, 0);
}
