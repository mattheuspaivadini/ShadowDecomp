#ifndef BOOT_GLOBALS_H
#define BOOT_GLOBALS_H

/* Official SHN_ABS global data objects exported by SCUS_974.72 to KERNEL.XFF
 * (Task D005; extracted from build/plan/xff/boot_shn_abs.tsv).
 *
 * Objects in .data/.rodata/.bss (outside the _gp window [0x00139D70..0x00149D6F])
 * use __attribute__((section(".data"))) or array declarations so ee-gcc -G8 emits
 * absolute (%hi/%lo) addressing rather than %gp_rel.
 * Objects in .sdata/.sbss (0x00139E00..0x0013A18F) use plain extern scalars.
 */

#define BOOT_ABS extern __attribute__((section(".data")))

/* --- .data (0x00131C00 .. 0x001360DF) --- */
extern unsigned char moduleInfo[0x48];                  /* 0x00131C00 */
extern unsigned char initialElfInfo[0x70];              /* 0x00131C48 */
extern unsigned char eeRegInfo[0x200];                  /* 0x00131D80 */
extern unsigned int  funcList[4];                       /* 0x00131F90 */
extern unsigned int  myaddr[4];                         /* 0x00131FC0 */
extern unsigned char _sceFs_q[0x80];                    /* 0x00132290 */
BOOT_ABS int         _kTLBRefillHandler;                /* 0x00132668 */
extern unsigned int  _kDebugHandler[16];                /* 0x00132670 */
BOOT_ABS int         _kExecArg;                         /* 0x001326B0 */
extern unsigned char TLBInfo[0x1C];                     /* 0x00132968 */
BOOT_ABS int         __sce_sema_id;                     /* 0x001329A0 */
BOOT_ABS int         __sce_eh_sema_id;                  /* 0x001329A4 */
extern unsigned char SysExecPS2Entry[0x18];             /* 0x00133150 */
extern int           dch[10];                           /* 0x001339B0 */
BOOT_ABS int         SCE_CD_debug;                      /* 0x00133A50 */
BOOT_ABS int         _sceCd_ncmd_semid;                 /* 0x00133A68 */
BOOT_ABS int         _sceCd_scmd_semid;                 /* 0x00133A6C */
BOOT_ABS int         _sceCd_rcmd_semid;                 /* 0x00133A70 */
BOOT_ABS int         _sceCd_c_cb_sem;                   /* 0x00133A74 */
BOOT_ABS int         _sceCd_ee_read_mode;               /* 0x00133A78 */
BOOT_ABS int         _sceCd_old_module;                 /* 0x00133A80 */
BOOT_ABS int         _sceCd_CdInit_ON;                  /* 0x00133A84 */
BOOT_ABS int         sceCdCbfunc_num;                   /* 0x00133AA0 */
BOOT_ABS int         sceCdCbfunc_number;                /* 0x00133AA4 */
extern unsigned char _sceCd_ncmdrdata[0x60];            /* 0x00133AC0 */
extern unsigned char _sceCd_ncmdsdata[0x1000];          /* 0x00133B40 */
extern unsigned char _sceCd_rd_intr_data[0x90];         /* 0x00134B40 */
extern unsigned char _sceCd_Read_cur_pos[0x10];         /* 0x00134C00 */
extern unsigned char _sceCd_cd_ncmd[0x28];              /* 0x00134C10 */
extern unsigned char _sceCd_scmdrdata[0x420];           /* 0x00134C40 */
extern unsigned char _sceCd_scmdsdata[0x408];           /* 0x00135080 */
extern unsigned char _sceCd_rcmdrdata[0x100];           /* 0x001354C0 */
extern unsigned char _sceCd_cd_scmd[0x28];              /* 0x001355C0 */
extern unsigned char gSceMc2SysInfo[0x308];             /* 0x00135638 */
BOOT_ABS int         _impure_ptr;                       /* 0x00135C60 */
extern unsigned int  __malloc_av_[258];                 /* 0x00135C68 */
BOOT_ABS unsigned long __malloc_trim_threshold;         /* 0x00136070 */
BOOT_ABS unsigned long __malloc_top_pad;                /* 0x00136078 */
BOOT_ABS int         __malloc_sbrk_base;                /* 0x00136080 */
BOOT_ABS unsigned long __malloc_max_sbrked_mem;         /* 0x00136088 */
BOOT_ABS unsigned long __malloc_max_total_mem;          /* 0x00136090 */
extern unsigned int  __malloc_current_mallinfo[10];     /* 0x00136098 */
BOOT_ABS int         __mb_cur_max;                      /* 0x001360C8 */

/* --- .rodata (0x00136100 .. 0x00139D57) --- */
extern const unsigned char __thenan_df[0x18];           /* 0x00139238 */
extern const unsigned char _ctype_[0x101];              /* 0x00139320 */
extern const double        __mprec_tens[25];            /* 0x00139B60 */
extern const double        __mprec_bigtens[5];          /* 0x00139C28 */
extern const double        __mprec_tinytens[5];         /* 0x00139C50 */
extern const double        __infinity[1];               /* 0x00139D50 */

/* --- .sdata / .sbss (0x00139E00 .. 0x0013A18F, %gp_rel) --- */
extern int HeapStart;                                   /* 0x00139E00 */
extern int ModuleStackStart;                            /* 0x0013A014 */
extern int spReg;                                       /* 0x0013A080 */
extern int loaderThreadId;                              /* 0x0013A084 */
extern int SCREEN_WIDTH;                                /* 0x0013A130 */
extern int SCREEN_HEIGHT;                               /* 0x0013A134 */
extern int errno;                                       /* 0x0013A18C */

/* --- .bss (0x0013A190 .. 0x0016A397) --- */
extern unsigned char key_value[0x400];                  /* 0x00169F98 */

#endif /* BOOT_GLOBALS_H */
