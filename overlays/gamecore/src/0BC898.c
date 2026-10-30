/* GAMECORE.XFF @ 0x0BC898 (56 B) - ScrSpriteParamSetup
 * Evidence: stores $ra, 0x0($sp); loads $ra, 0x0($sp); calls j iosFree; frame
 * UNCONFIRMED: the 16-byte copy is a packed two-qword struct assignment, which
 * is what makes the image use ldl/ldr + sdl/sdr instead of ld/sd.
 
 */
void iosFree(void *p);

struct Packed16 {
    unsigned long long a;
    unsigned long long b;
} __attribute__((packed));

void ScrSpriteParamSetup(char *dst, char *src) {
    *(struct Packed16 *)dst = *(struct Packed16 *)src;
    iosFree(src);
}
