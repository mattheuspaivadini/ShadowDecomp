/* C equivalent of scePad2CreateSocket (0150B0, 264 B @ 0x001150B0).
 *
 * Reconstructed instruction-by-instruction from asm/cod/0150B0.s and the
 * REA/Ghidra Emotion Engine dossier ev_77e41be23974c7514b0b38cd9ab226ddb73d844786c72d924e6ef9d649b1bbe4.
 * This is the readable reconstruction: it is NOT byte-exact and is not part of
 * the build.  The codegen-tuned near-miss (2 diff instructions) is
 * src/non_matching/0150B0.c.
 *
 * Behaviour derived from the target:
 *   150C8  andi v0,s1,0x3F / beqz   -> the buffer must be 64-byte aligned
 *   150D4  scePrintf(D_00138560)    -> no argument is passed with the format
 *   150E8  beql a2,zero             -> param == NULL uses the zeroed request
 *   15110  ldl/ldr + sdl/sdr (x2)   -> the 16-byte name block is copied as a
 *                                      byte-aligned (unaligned-safe) copy
 *   1514C  li s2,1 / sw s2,4(sp)    -> request[1] = 1, request[0] |= 1
 *   15164  jal sceDbcCreateSocket   -> (req, buf, buf + 0x80)
 *   15170  bltz s0                  -> negative result is returned as-is
 *   15188  addu a1,v1,v0            -> D_0014B598[s]: stride 0x334
 *   15190  sw s1,0x10(a1)           -> record->buf = buf
 *   15198  sw s2,0(v0)              -> record->in_use = 1
 *   15194  jal func_001155D8(s)
 */
typedef unsigned int u_long128 __attribute__((mode(TI)));

struct pad2_name {                  /* 16-byte name block: byte-aligned copy */
    unsigned char c[16];
};

struct pad2_param {                 /* caller-visible socket parameters */
    int f00;                        /* 0x00 */
    int f04;                        /* 0x04 */
    int f08;                        /* 0x08 */
    int f0C;                        /* 0x0C */
    struct pad2_name name;          /* 0x10 */
};

struct pad2_request {               /* request block built on the stack */
    int flags;                      /* 0x00: bit 0 marks the record in use */
    int one;                        /* 0x04: always 1 */
    int f08;                        /* 0x08 */
    int f0C;                        /* 0x0C */
    int f10;                        /* 0x10 */
    struct pad2_name name;          /* 0x14 */
};

struct pad2_socket {                /* D_0014B598[], stride 0x334 */
    int  in_use;                    /* 0x00 */
    char pad04[0x0C];
    int  buf;                       /* 0x10: the 64-byte aligned buffer */
    char pad14[0x334 - 0x14];
};

extern struct pad2_socket D_0014B598[];
extern char D_00138560[];           /* "libpad2: buffer addr is not 64 byte align. %08x\n" */

int scePrintf(const char *fmt, ...);
int sceDbcCreateSocket(struct pad2_request *req, int buf, int end);
void func_001155D8(int index);      /* UNCONFIRMED: per-socket notification */

int scePad2CreateSocket(struct pad2_param *param, int buf)
{
    struct pad2_request req;
    int s;

    if (buf & 0x3F) {
        /* the image passes the format alone (no %08x argument) */
        scePrintf(D_00138560);
        return -1;
    }

    if (param != 0) {
        req.flags = param->f00;
        req.f08 = param->f04;
        req.f0C = param->f08;
        req.f10 = param->f0C;
        req.name = param->name;
    } else {
        req.flags = 0;
        req.f08 = 0;
        req.f0C = 0;
        req.f10 = 0;
        req.name.c[0] = 0;
    }
    req.one = 1;
    req.flags |= 1;

    s = sceDbcCreateSocket(&req, buf, buf + 0x80);
    if (s < 0)
        return s;

    D_0014B598[s].buf = buf;
    D_0014B598[s].in_use = 1;
    func_001155D8(s);
    return s;
}
