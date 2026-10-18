/* asm/cod/013530.s -> sceGsResetPath.
 * sceGsResetPath; u_long128 FIFO copy + VU0 asm; TU built with dtls13010 -g0 (jr slot filled) (Session 22)
 * MATCHED. */
typedef unsigned int u_long128 __attribute__((mode(TI)));
#define VIF1_FBRST ((volatile unsigned int *)0x10003C10)
#define VIF1_ERR   ((volatile unsigned int *)0x10003C20)
#define VIF1_FIFO  ((volatile u_long128 *)0x10005000)
#define GIF_CTRL   ((volatile unsigned int *)0x10003000)

extern u_long128 D_00133980[2];

void sceGsResetPath(void) {
    unsigned int tmp = 0;

    *VIF1_FBRST = 1;
    *VIF1_ERR = 2;
    __asm__ __volatile__("sync" ::: "memory");
    __asm__ __volatile__("cfc2.ni %0, $vi28
	ori %0, %0, 0x200
	ctc2.ni %0, $vi28
	sync.p" : "+r"(tmp));
    *VIF1_FIFO = D_00133980[0];
    *VIF1_FIFO = D_00133980[1];
    *GIF_CTRL = 1;
}
