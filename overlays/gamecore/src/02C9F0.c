/* GAMECORE.XFF @ 0x02C9F0 (56 B) - stagemanager_getNbWorldLayoutDatas
 * Evidence: no loads/stores; data <.data>+0x8c440fb8, <.data>+0x8c430fbc
 */
/* variant d: ternary chain */
struct WorldLayoutData {
    char pad[0x34];
    int countA;
    int countB;
};

extern struct WorldLayoutData *D_kernel_data_0FB8;
extern void *D_kernel_data_0FBC;

int stagemanager_getNbWorldLayoutDatas(void) {
    return (D_kernel_data_0FB8 == 0 || D_kernel_data_0FBC == 0)
               ? 0
               : D_kernel_data_0FB8->countA * D_kernel_data_0FB8->countB;
}
