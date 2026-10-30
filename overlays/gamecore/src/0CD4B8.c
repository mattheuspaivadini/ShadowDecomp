/* GAMECORE.XFF @ 0x0CD4B8 (52 B) - getWeaponName
 * Evidence: `lw $v0,0x0(DldSysUndefSymbol)`, `lui/addiu SH_WeaponListDEFAULT`,
 * `sll 3`/`subu`/`sll 2` (stride 0x1C), `xor $v0,$v0,$a1` + `movz
 * $a1,$zero,$v0`, `lw 0x10($a1)`, `addu`, `lw 0x0($v1)`.
 * UNCONFIRMED: the `xor`/`movz` pair is reproduced as a ternary against 0; the
 * real source shape of that DldSys indirection is unknown
 
 */
extern int DldSysUndefSymbol;
extern int SH_WeaponListDEFAULT[];

int getWeaponName(int idx) {
    int *list = (DldSysUndefSymbol != (int)SH_WeaponListDEFAULT) ? SH_WeaponListDEFAULT : 0;
    return *(int *)(idx * 0x1c + list[4]);
}
