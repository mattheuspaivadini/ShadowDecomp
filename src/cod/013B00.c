/* asm/cod/013B00.s -> sceGsSwapDBuff.
 * sceGsSwapDBuff (SHN_ABS)
 * MATCHED (Session 12). */
void sceGsPutDispEnv(void *env);
void sceGsPutDrawEnv(void *env);

void sceGsSwapDBuff(char *p, int flag) {
    int f = flag & 1;

    sceGsPutDispEnv(p + f * 0x28);
    if (f) {
        sceGsPutDrawEnv(p + 0x140);
        __asm__ volatile("");
        return;
    } else {
        sceGsPutDrawEnv(p + 0x50);
        __asm__ volatile("");
        return;
    }
}
