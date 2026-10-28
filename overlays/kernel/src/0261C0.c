/* KERNEL.XFF @ 0x0261C0 (64 B) - Sg2SepAllStopSndOff
 * Evidence: Sg2SepStopSndOff(i) for the 32 SEP ids (the int return keeps v0 live, so the loop test uses v1); returns 0.
 */
int Sg2SepStopSndOff(int id);
int Sg2SepAllStopSndOff(void) {
 int i;
 for (i = 0; i < 32; i++) { Sg2SepStopSndOff(i); }
 return 0;
}
