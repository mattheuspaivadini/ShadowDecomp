/* KERNEL.XFF @ 0x029E58 (180 B) - Sg2SlotSetLfoPitchSpeed
 * STATUS: NOT MATCHING, 11 of 45 words differ (same size). Not in c_sources.txt.
 * Shape: speed != 0 -> speed = 240 / (60 - speed * 58 / 127) (two divides with register divisors: li 127 / li 60, break-7 checks);
 * slot (0xE0 B, .bss+0x97E30)->+0x78 = speed, ->+0x80 = 0; if (speed && slot->+0x7C) flags |= 0x400 else flags &= ~0x400.
 * The image keeps t0 = 224*i and a0 = bss base as separate regs and copies the lfo pointer twice (move v0,t0 / move v1,v0)
 * around the two stores. Tried: flat int fields (this file, 11 diff), nested struct Lfo + s/l pointer vars (156 B, branches merged).
 * UNCONFIRMED: field names.
 */
struct Sg2Pitch { int unk0; int unk4; int speed; int depth; int unk10; int unk14; };
struct Sg2Slot { unsigned int flags; char pad04[0x6C]; struct Sg2Pitch pitch; char pad88[0x58]; };
extern struct Sg2Slot D_kernel_bss_97E30[48];
#define slot D_kernel_bss_97E30

void Sg2SlotSetLfoPitchSpeed(int i, int speed) {
    int v;

    v = speed;
    if (v != 0) v = 240 / (60 - speed * 58 / 127);
    slot[i].pitch.speed = v;
    slot[i].pitch.unk10 = 0;
    if (v != 0 && slot[i].pitch.depth != 0) {
        slot[i].flags |= 0x400;
    } else {
        slot[i].flags &= ~0x400;
    }
}
