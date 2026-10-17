/* asm/cod/00EEB8.s -> sceSifSetIopAddr.
 * SCE libkernel sif; early-return error form selects movn (Session 19)
 * MATCHED. */
int func_0010E238(void);
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

extern int D_00147380[];   /* .data/.bss outside small-data -> lui/%lo */
extern int D_00147580[];   /* .data/.bss transfer buffer     -> lui/addiu */

int sceSifSetIopAddr(int a0, void *a1, int a2) {
    if (func_0010E238() < 0)
        return 0xFFFF0000;
    D_00147380[0] = a0;
    D_00147380[1] = a2;
    if (a2 == 0)
        *(unsigned char *)&D_00147380[2] = *(unsigned char *)a1;
    else if (a2 == 1)
        *(unsigned short *)&D_00147380[2] = *(unsigned short *)a1;
    else if (a2 == 2)
        D_00147380[2] = *(int *)a1;
    else
        return 0xFFFEFFFE;
    if (sceSifCallRpc((int)D_00147580, 2, 0, (int)D_00147380, 0x20,
                          (int)D_00147380, 0x10, 0, 0) < 0)
        return 0xFFFEFFFF;
    return 0;
}
