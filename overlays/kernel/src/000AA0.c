/* KERNEL.XFF @ 0x000AA0 (40 B) - iosDeleteSema
 * Evidence: frame 0x10 (saves $s0 and $ra), `$s0 = $a0` in the jal delay slot of
 * LoaderSysDeleteExternalSemaList (the argument is forwarded), then $a0 = $s0
 * and a sibling `j DeleteSema` with the frame released in its delay slot.
 * Both callees are SHN_ABS imports from the boot ELF.
 */
int LoaderSysDeleteExternalSemaList(int sema);
int DeleteSema(int sema);

void iosDeleteSema(int sema) {
    LoaderSysDeleteExternalSemaList(sema);
    DeleteSema(sema);
}
