/* KERNEL.XFF @ 0x033678 (216 B) - floorf
 * Evidence: fdlibm sf_floor.c (huge = 1.0e30 = 0x7149F2C9). The image's Newlib is newer than the 1.9 tree in build/s17/nl19 (whose fdlibm.h has no FLT_UWORD macros): it is built with the R5900 settings _FLT_LARGEST_EXPONENT_IS_NORMAL (FLT_UWORD_IS_FINITE = 1, no inf/NaN path) and _FLT_NO_DENORMALS (FLT_UWORD_IS_ZERO = x < 0x00800000, FLT_SMALLEST_EXP = 1); those macro values are reproduced locally.
 */
/* ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com. */

typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef union
{
  float value;
  __uint32_t word;
} ieee_float_shape_type;
#define GET_FLOAT_WORD(i,d) do { ieee_float_shape_type gf_u; gf_u.value = (d); (i) = gf_u.word; } while (0)
#define SET_FLOAT_WORD(d,i) do { ieee_float_shape_type sf_u; sf_u.word = (i); (d) = sf_u.value; } while (0)
#define FLT_UWORD_IS_ZERO(x) ((x)<0x00800000L)
#define FLT_UWORD_IS_FINITE(x) 1

static const float huge = 1.0e30;

float floorf(float x)
{
	__int32_t i0,j0;
	__uint32_t i,ix;
	GET_FLOAT_WORD(i0,x);
	ix = (i0&0x7fffffff);
	j0 = (ix>>23)-0x7f;
	if(j0<23) {
	    if(j0<0) { 	/* raise inexact if x != 0 */
		if(huge+x>(float)0.0) {/* return 0*sign(x) if |x|<1 */
		    if(i0>=0) {i0=0;}
		    else if(!FLT_UWORD_IS_ZERO(ix))
			{ i0=0xbf800000;}
		}
	    } else {
		i = (0x007fffff)>>j0;
		if((i0&i)==0) return x; /* x is integral */
		if(huge+x>(float)0.0) {	/* raise inexact flag */
		    if(i0<0) i0 += (0x00800000)>>j0;
		    i0 &= (~i);
		}
	    }
	} else {
	    if(!FLT_UWORD_IS_FINITE(ix)) return x+x;	/* inf or NaN */
	    else return x;		/* x is integral */
	}
	SET_FLOAT_WORD(x,i0);
	return x;
}
