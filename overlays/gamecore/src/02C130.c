/* GAMECORE.XFF @ 0x02C130 (52 B) - GetStageCenter
 * Evidence: frame 0x50, `$a1` stored into the local at +0x4 in the `jal`
 * delay slot (`$a0 = $sp`), then `lq $v1,0x30($sp)` / `sq $v1,0($s0)` into the
 * caller's output pointer. The callee must return a value, otherwise the
 * `lq`/`sq` scratch register becomes `$v2` instead of `$v1`.
 * UNCONFIRMED: the work struct layout and the callee prototype.
 
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

struct StageCenterWork {
    char pad[4];
    int stage;
    char pad30[0x28];
    u_long128 center;
};

int func_02B3C8(struct StageCenterWork *work);

void GetStageCenter(void *out, int stage) {
    struct StageCenterWork work;

    work.stage = stage;
    func_02B3C8(&work);
    *(u_long128 *)out = work.center;
}
