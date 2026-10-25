/* KERNEL.XFF @ 0x02DC00 (84 B) - Sg2VabClose
 * Evidence: returns -1 unless vab_check_alive(id); then Sg2SmfpVabStopSndOff(id), Sg2SepVabStopSndOff(id) and a sibling call of the static at .text+0x2DC58 (id). UNCONFIRMED: callee name.
 */
int vab_check_alive(int id);
void Sg2SmfpVabStopSndOff(int id);
void Sg2SepVabStopSndOff(int id);
int func_02DC58(int id);

int Sg2VabClose(int id) {
    if (vab_check_alive(id) == 0) {
        return -1;
    }
    Sg2SmfpVabStopSndOff(id);
    Sg2SepVabStopSndOff(id);
    return func_02DC58(id);
}
