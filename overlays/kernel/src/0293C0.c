/* KERNEL.XFF @ 0x0293C0 (88 B) - Sg2SlotCheckSlotClass
 * Evidence: returns 1 when one of the 48 slots has bit 0 set and word +0xC == cls (ret variable + break), else 0.
 */
struct Sg2Slot {
    unsigned int flags;
    int owner;
    int unk8;
    int cls;
    char pad[0xE0 - 0x10];
};
extern struct Sg2Slot D_kernel_bss_97E30[48];

int Sg2SlotCheckSlotClass(int cls) {
    struct Sg2Slot *s = D_kernel_bss_97E30;
    int ret = 0;
    int i;

    for (i = 0; i < 48; i++, s++) {
        if ((s->flags & 1) && s->cls == cls) {
            ret = 1;
            break;
        }
    }
    return ret;
}
