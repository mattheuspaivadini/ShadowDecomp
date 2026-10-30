/* GAMECORE.XFF @ 0x007D00 (60 B) - camdebug_for_new_camera
 * Evidence: two `jal iosGetTCountExtension` calls whose 8-byte results are
 * stored at gcGlobalVar+0xD0 and +0xD8, with `jal .text+0x5278` in between.
 * UNCONFIRMED: the gcGlobalVar fields and the middle callee.
 
 */
struct GcGlobal {
    char pad[0xD0];
    long d0;
    long d8;
};

extern struct GcGlobal gcGlobalVar;
long iosGetTCountExtension(void);
void func_005278(void);

void camdebug_for_new_camera(void) {
    gcGlobalVar.d0 = iosGetTCountExtension();
    func_005278();
    gcGlobalVar.d8 = iosGetTCountExtension();
}
