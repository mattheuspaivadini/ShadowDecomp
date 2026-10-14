/* STATUS (Session 4, 2026-10-14): NON_MATCHING. if-chain: our chain emits `bnel` skips where the original emits `beq` to shared case blocks; a `switch` becomes a range check + jump table.
 * The original .s stays in the build (asm/cod/017A00.s); this C
 * attempt is kept for the record. */
/* asm/cod/017A00.s -> func_00117A00 @ 0x00117A00 (0xB0 bytes)
 * A chain of `li v0, CONST; beq a0, v0, case` comparisons in source order
 * (0x8001, 0x8003, 0x8002, 0x8004, 0x8011, 0x8013, 0x8012, 0x8014), each
 * storing a table address (or a loaded pointer) into *out; the default stores 0.
 * Every path returns 1.
 *
 * D_00133A68 / D_00133A6C are loaded as 32-bit values (their *contents* are
 * stored); the others are addresses (declared as arrays so they are absolute,
 * not small data).
 */
extern int D_00133A68[];
extern int D_00133A6C[];
extern char D_00133AC0[];
extern char D_00133B40[];
extern char D_00134C10[];
extern char D_00134C40[];
extern char D_00135080[];
extern char D_001355C0[];

int func_00117A00(int id, int *out) {
    switch (id) {
    case 0x8001:
        *out = D_00133A68[0];
        break;
    case 0x8003:
        *out = (int)D_00133AC0;
        break;
    case 0x8002:
        *out = (int)D_00133B40;
        break;
    case 0x8004:
        *out = (int)D_00134C10;
        break;
    case 0x8011:
        *out = D_00133A6C[0];
        break;
    case 0x8013:
        *out = (int)D_00134C40;
        break;
    case 0x8012:
        *out = (int)D_00135080;
        break;
    case 0x8014:
        *out = (int)D_001355C0;
        break;
    default:
        *out = 0;
        break;
    }
    return 1;
}
