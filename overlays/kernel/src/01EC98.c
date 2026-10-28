/* KERNEL.XFF @ 0x01EC98 (44 B) - iosGetIopTotalMemSize
 * Evidence: LoaderSysCheckCDBootMode() == 0 -> 0x800000 (8 MB IOP RAM) else 0x200000 (2 MB); movn select, the zero test written first. UNCONFIRMED: meaning of the boot-mode flag.
 */
int LoaderSysCheckCDBootMode(void);
int iosGetIopTotalMemSize(void) {
 if (!LoaderSysCheckCDBootMode()) return 0x800000;
 return 0x200000;
}
