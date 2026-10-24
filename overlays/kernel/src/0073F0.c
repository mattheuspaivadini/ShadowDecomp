/* KERNEL.XFF @ 0x0073F0 (12 B) - Init_Controler
 * Evidence: `sh $zero,0x0($a0)` / `jr $ra` / `sh $zero,0x2($a0)` (16-bit
 * stores, no relocation). Two halfword fields cleared; the source order that
 * reproduces the image is the descending one (sched2/reorg issue the pair
 * reversed), see KERNEL.XFF STATUS notes.
 */
void Init_Controler(short *p) {
    p[1] = 0;
    p[0] = 0;
}
