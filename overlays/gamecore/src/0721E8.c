/* GAMECORE.XFF @ 0x0721E8 (52 B) - demo_op2_resetHorseBridle
 * Evidence: `jal gStatGetHorseDemoISYSObj`, a zero test that returns early,
 * then a sibling `j` to `nico_resetHorseRidingStatusForHorse` with
 * `$a0 = $v0` in the delay slot.
 * UNCONFIRMED: the callee prototypes.
 
 */
int gStatGetHorseDemoISYSObj(void);
void nico_resetHorseRidingStatusForHorse(int obj);

void demo_op2_resetHorseBridle(void) {
    int obj = gStatGetHorseDemoISYSObj();

    if (obj != 0)
        nico_resetHorseRidingStatusForHorse(obj);
}
