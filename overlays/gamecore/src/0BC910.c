/* GAMECORE.XFF @ 0x0BC910 (64 B) - spritemenudisplaytriggerpad_group
 * Evidence: stores $ra, 0x0($sp), $v0, 0x0($v1); loads $v0, 0x0($v1); relocs <.data>; calls isysGetThisSubThread, GetSpriteMenuClass, scrRun; frame
 
 */
int isysGetThisSubThread(void);
int GetSpriteMenuClass(int thread);
void scrRun(void);
extern int D_kernel_data_172C;

void spritemenudisplaytriggerpad_group(void) {
    GetSpriteMenuClass(isysGetThisSubThread());
    D_kernel_data_172C = D_kernel_data_172C + 1;
    for (;;)
        scrRun();
}
