/* GAMECORE.XFF @ 0x056BA8 (56 B) - st_malloc_test
 * Evidence: `scrInit(isysGetThisSubThread())` (`$a0 = $v0` in the `jal scrInit`
 * delay slot), then a backward `b` covering `scrRunM(0xB4)` and
 * `iosDebugPrintHashTable(rootPtn)`.
 * UNCONFIRMED: the callee prototypes.
 
 */
void *isysGetThisSubThread(void);
void scrInit(void *thread);
void scrRunM(int frames);
void iosDebugPrintHashTable(void *root);
extern float rootPtn[];

void st_malloc_test(void) {
    scrInit(isysGetThisSubThread());
    while (1) {
        scrRunM(0xB4);
        iosDebugPrintHashTable(rootPtn);
    }
}
