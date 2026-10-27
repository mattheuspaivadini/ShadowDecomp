/* KERNEL.XFF @ 0x033750 (200 B) - scalbnf
 * Evidence: fdlibm sf_scalbn.c (overflow test k > 0xFF, underflow k < 1 with the n > 50000 split, both through copysignf). The image's Newlib is newer than the 1.9 tree in build/s17/nl19 (whose fdlibm.h has no FLT_UWORD macros): it is built with the R5900 settings _FLT_LARGEST_EXPONENT_IS_NORMAL (FLT_UWORD_IS_FINITE = 1, no inf/NaN path) and _FLT_NO_DENORMALS (FLT_UWORD_IS_ZERO = x < 0x00800000, FLT_SMALLEST_EXP = 1); those macro values are reproduced locally.
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
#define FLT_UWORD_IS_SUBNORMAL(x) 0
#define FLT_UWORD_MAX 0x7fffffffL
#define FLT_LARGEST_EXP (FLT_UWORD_MAX>>23)
#define FLT_SMALLEST_EXP 1

float copysignf(float x, float y);

static const float
two25   =  3.355443200e+07,	/* 0x4c000000 */
twom25  =  2.9802322388e-08,	/* 0x33000000 */
huge   = 1.0e+30,
tiny   = 1.0e-30;

float scalbnf (float x, int n)
{
	__int32_t  k,ix;
	__uint32_t hx;

	GET_FLOAT_WORD(ix,x);
	hx = ix&0x7fffffff;
        k = hx>>23;		/* extract exponent */
	if (FLT_UWORD_IS_ZERO(hx))
	    return x;
        if (!FLT_UWORD_IS_FINITE(hx))
	    return x+x;		/* NaN or Inf */
        if (FLT_UWORD_IS_SUBNORMAL(hx)) {
	    x *= two25;
	    GET_FLOAT_WORD(ix,x);
	    k = ((ix&0x7f800000)>>23) - 25;
            if (n< -50000) return tiny*x; 	/*underflow*/
        }
        k = k+n;
        if (k > FLT_LARGEST_EXP) return huge*copysignf(huge,x); /* overflow  */
        if (k > 0) 				/* normal result */
	    {SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23)); return x;}
        if (k < FLT_SMALLEST_EXP) {
            if (n > 50000) 	/* in case integer overflow in n+k */
		return huge*copysignf(huge,x);	/*overflow*/
	    else return tiny*copysignf(tiny,x);	/*underflow*/
        }
        k += 25;				/* subnormal result */
	SET_FLOAT_WORD(x,(ix&0x807fffff)|(k<<23));
        return x*twom25;
}
