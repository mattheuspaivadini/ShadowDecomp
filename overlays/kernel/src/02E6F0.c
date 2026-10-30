/* KERNEL.XFF @ 0x02E6F0 (432 B) - func_02E6F0 (static, no symbol in the shipped .symtab)
 * STATUS: MATCHING [-G0 -fno-strict-aliasing] 0/108 words differ
 * Evidence: voice envelope/volume setter. `sll/addu/sll/addu/sll` in the prologue is
 *   idx*0xC4, so the record array has stride 0xC4 and the fields live in a sub-struct at
 *   +0x14 (kept in $s1 for the whole body). DIntr() (sym 1122) returns the saved interrupt
 *   state (kept for the final `if (state) EIntr();`, sym 1247, emitted as a `j` sibcall);
 *   Sg2CtrlGetTickMode() (sym 49) returns the tick rate. rate = vol / (1000.0f / tick),
 *   clamped up to 1.0f (c.lt.s + bc1tl + mov.s). `if (val) e->unk08 = val, e->flags |= 4`.
 *   The two float arguments f12/f13 are compared as `(float)(int)x == -1000.0f`
 *   (cvt.w.s/mfc1/cvt.s.w/c.eq.s proves the int round-trip, so the C casts through int);
 *   each accepted value stores the target (0xC / 0x10), sets flags bit 1 / 2 and stores
 *   the ramp (x - prev) / rate at 0x14 / 0x18, with the previous values read at 0x64 / 0x60.
 *   `if (e->flags) e->state = 1;` closes the body.
 * Levers tried: struct stride 0xC4 with the pad tail (0x7C was wrong -> 400 B, this fix
 *   gave the match); -1000 test as int compare (`li -1000; beq`) vs float compare (no
 *   cvt round-trip) vs (float)(int) cast (the image's 6-instruction sequence);
 *   rate as two statements vs one expression (identical); int locals for the casts;
 *   -g0 / -fno-schedule-insns2 / -fno-gcse (all worse or equal).
 * UNCONFIRMED: all field names except DIntr/EIntr/Sg2CtrlGetTickMode; the env sub-struct
 *   layout (only 0x00,0x04,0x08,0x0C,0x10,0x14,0x18,0x60,0x64 are evidenced); whether
 *   the -1000 test is a cast in the original source or a macro.
 */

struct Sg2Env {
    int state;
    int flags;
    int unk08;
    float target1;
    float target2;
    float slope1;
    float slope2;
    char pad1C[0x60 - 0x1C];
    float unk60;
    float unk64;
    char pad68[0xB0 - 0x68];
};
struct Sg2Voice {
    char pad0[0x14];
    struct Sg2Env env;
};

int DIntr(void);
void EIntr(void);
int Sg2CtrlGetTickMode(void);

void func_02E6F0(struct Sg2Voice *base, int idx, int vol, int val, float f12, float f13) {
    struct Sg2Env *e = &base[idx].env;
    int state;
    float prev1;
    float prev2;
    float rate;

    state = DIntr();
    prev1 = e->unk64;
    prev2 = e->unk60;
    rate = 1000.0f / Sg2CtrlGetTickMode();
    rate = vol / rate;
    if (rate < 1.0f) {
        rate = 1.0f;
    }
    if (val) {
        e->unk08 = val;
        e->flags |= 4;
    }
    if ((float)(int)f12 != -1000.0f) {
        e->target1 = f12;
        e->flags |= 1;
        e->slope1 = (f12 - prev1) / rate;
    }
    if ((float)(int)f13 != -1000.0f) {
        e->target2 = f13;
        e->flags |= 2;
        e->slope2 = (f13 - prev2) / rate;
    }
    if (e->flags) {
        e->state = 1;
    }
    if (state) {
        EIntr();
    }
}
