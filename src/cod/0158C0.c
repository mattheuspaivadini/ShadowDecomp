/* asm/cod/0158C0.s -> sceVibGetProfile.
 * sceVibGetProfile; u_long bitfield request word passed by value to sceDbcReceiveData (Session 22)
 * MATCHED. */
typedef struct {
    unsigned long f0:14;
    unsigned long f1:2;
    unsigned long f2:8;
    unsigned long f3:8;
} DbcParam;

int sceDbcReceiveData(int port, DbcParam param, void *buf, int slot);

int sceVibGetProfile(int port, int slot) {
    DbcParam p;
    int buf;
    int r;

    p.f0 = 2;
    p.f1 = 2;
    p.f2 = 3;
    p.f3 = 1;
    r = sceDbcReceiveData(port, p, &buf, slot);
    if (r >= 0)
        return buf;
    return r;
}
