/* asm/cod/00EDC8.s -> sceSifGetIopAddr.
 * SCE libkernel sif; same if-chain template as sceSifSetIopAddr (Session 19)
 * MATCHED. */
int func_0010E238(void);
int sceSifCallRpc(int a0, int a1, int a2, int a3, int a4, int a5, int a6,
                  int a7, int a8);

extern int D_00147380[];   /* .data/.bss outside small-data -> lui/%lo */
extern int D_00147580[];   /* .data/.bss transfer buffer     -> lui/addiu */

int sceSifGetIopAddr(int a0, void *a1, unsigned int a2) {
    if (func_0010E238() < 0)
        return 0xFFFF0000;
    if (a2 >= 3)
        return 0xFFFEFFFE;
    D_00147380[0] = a0;
    D_00147380[1] = a2;
    if (sceSifCallRpc((int)D_00147580, 3, 0, (int)D_00147380, 0x20,
                      (int)D_00147380, 0x20, 0, 0) < 0)
        return 0xFFFEFFFF;
    if (a2 == 0)
        *(unsigned char *)a1 = *(unsigned char *)&D_00147380[0];
    else if (a2 == 1)
        *(unsigned short *)a1 = *(unsigned short *)&D_00147380[0];
    else if (a2 == 2)
        *(int *)a1 = D_00147380[0];
    else
        return 0xFFFEFFFE;
    return 0;
}
