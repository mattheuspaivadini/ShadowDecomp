/* GAMECORE.XFF @ 0x01D810 (44 B) - opflowOp2End
 * Evidence: word read-modify-write of .data+0xA50: `andi 1`, `sll 3`,
 * `ori 4`, `and ~8` (`-0x9`), `or`: bit 2 is set and bits 3.. are replaced by
 * the argument's low bit.
 * UNCONFIRMED: the flag word meaning and the argument's meaning.
 
 */
extern int D_kernel_data_0A50[];

void opflowOp2End(int flag) {
    D_kernel_data_0A50[0] = ((D_kernel_data_0A50[0] | 4) & ~8) | ((flag & 1) << 3);
}
