/* KERNEL.XFF @ 0x029F10 (164 B) - Sg2SlotSetLfoPitchDepth   [MATCH: -G0 -fno-strict-aliasing]
 * Evidence: 48 voice slots of 0xE0 B at .bss+0x97E30 (idx*0xE0 = (idx*7)<<5).
 * `lw 0x7E34(base + idx*0xE0)` is slot[i].owner (+0x04) == 1 (compare against
 * addiu 1); the value `depth ? (owner==1 ? depth*2 : depth) : 0` is stored at
 * slot+0x70+0xC = +0x7C, i.e. inside the LFO-pitch sub-object at +0x70 (the
 * image's other base `a3 = idx*0xE0 + 0x70`, address = sym + (offset+0x70)).
 * Flag 0x400 is raised only when the *parameter* depth != 0 (the second
 * `beqz $a1`) and +0x78 != 0, else cleared; both clearing paths share one
 * block.  UNCONFIRMED: field names beyond owner/speed/depth.
 * Lever: the nested ternary with an unconditional store (the store is not
 * inside the `depth != 0` block; the image re-tests depth before it), plus the
 * nested-member form `slot[i].pitch.depth` for the +0x70-based address.
 */
struct Sg2Pitch { int unk0; int unk4; int speed; int depth; int unk10; int unk14; };
struct Sg2Slot { unsigned int flags; int owner; char pad08[0x68]; struct Sg2Pitch pitch; char pad88[0x58]; };
extern struct Sg2Slot D_kernel_bss_97E30[48];
#define slot D_kernel_bss_97E30

void Sg2SlotSetLfoPitchDepth(int i, int depth) {
    int v;

    v = depth ? (slot[i].owner == 1 ? depth * 2 : depth) : 0;
    slot[i].pitch.depth = v;
    if (depth != 0 && slot[i].pitch.speed != 0) {
        slot[i].flags |= 0x400;
    } else {
        slot[i].flags &= ~0x400;
    }
}
