/* asm/cod/00A120.s -> func_0010A120.
 * SCE SDK, cc=29 (callee return types / statement shape from the image)
 * MATCHED. */
extern int  D_00132320 __attribute__((section(".data")));
extern char D_00146EC0[];   /* .bss 0x200 bytes = 32 x 0x10 records */

void func_0010A0B0(void);
int WaitSema(int a0);
void SignalSema(int a0);

int func_0010A120(void) {
    int  count = 0;
    int *p;
    int *end;

    func_0010A0B0();
    WaitSema(D_00132320);
    for (p = (int *)D_00146EC0; p < (int *)D_00146EC0 + 0x80; p += 4) {
        if (p[1] != 0)
            count++;
    }
    SignalSema(D_00132320);
    return count;
}
