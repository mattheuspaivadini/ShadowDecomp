/* libgcc2.h - the GCC 2.95.3 gcc/libgcc2.c type section, as configured for
 * the EE (little-endian MIPS R5900: LIBGCC2_WORDS_BIG_ENDIAN 0, 32-bit SItype
 * words, DImode = long long, DFtype soft-float through the dp* libcalls).
 * Transcribed from gcc-2.95.3 gcc/libgcc2.c; longlong.h is the matching
 * gcc-2.95.3 gcc/longlong.h. */
#ifndef LIBGCC2_H
#define LIBGCC2_H

#define BITS_PER_UNIT 8
#define LIBGCC2_WORDS_BIG_ENDIAN 0
#define LIBGCC2_LONG_DOUBLE_TYPE_SIZE 64

typedef unsigned int UQItype	__attribute__ ((mode (QI)));
typedef 	 int SItype	__attribute__ ((mode (SI)));
typedef unsigned int USItype	__attribute__ ((mode (SI)));
typedef		 int DItype	__attribute__ ((mode (DI)));
typedef unsigned int UDItype	__attribute__ ((mode (DI)));

typedef 	float SFtype	__attribute__ ((mode (SF)));
typedef		float DFtype	__attribute__ ((mode (DF)));

#if LIBGCC2_LONG_DOUBLE_TYPE_SIZE == 96
typedef		float XFtype	__attribute__ ((mode (XF)));
#endif
#if LIBGCC2_LONG_DOUBLE_TYPE_SIZE == 128
typedef		float TFtype	__attribute__ ((mode (TF)));
#endif

typedef int word_type __attribute__ ((mode (__word__)));


#define SI_TYPE_SIZE (sizeof (SItype) * BITS_PER_UNIT)

/* DIstructs are pairs of SItype values in the order determined by
   LIBGCC2_WORDS_BIG_ENDIAN.  */

#if LIBGCC2_WORDS_BIG_ENDIAN
  struct DIstruct {SItype high, low;};
#else
  struct DIstruct {SItype low, high;};
#endif

/* We need this union to unpack/pack DImode values, since we don't have
   any arithmetic yet.  Incoming DImode parameters are stored into the
   `ll' field, and the unpacked result is read from the struct `s'.  */

typedef union
{
  struct DIstruct s;
  DItype ll;
} DIunion;

#include "longlong.h"

#endif /* LIBGCC2_H */
