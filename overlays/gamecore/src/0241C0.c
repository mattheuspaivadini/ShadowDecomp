/* GAMECORE.XFF @ 0x0241C0 (60 B) - DeleteSeamlessStageLoad
 * Evidence: `$s0 = .data+0xA90`, `lw 0x8($s0)` guard, `jal iosFree` with the
 * value in `$a0`, then `sw $zero,0x8($s0)`.
 * UNCONFIRMED: the `.data` block's name.
 
 */
extern char D_kernel_data_0000[];
void iosFree(void *ptr);

struct SeamlessStageLoad {
    int pad0;
    int pad1;
    void *data;
};

void DeleteSeamlessStageLoad(void) {
    struct SeamlessStageLoad *load =
        (struct SeamlessStageLoad *)(D_kernel_data_0000 + 0xA90);

    if (load->data != 0) {
        iosFree(load->data);
        load->data = 0;
    }
}
