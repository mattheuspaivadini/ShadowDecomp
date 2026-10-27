/* KERNEL.XFF @ 0x031D88 (464 B) - __ieee754_fmodf
 * Evidence: fdlibm ef_fmod.c (fixed-point shift-subtract loop; Zero[] = {0.0, -0.0} is the function's own .rodata table, masked by the relocation). Newlib float libm built with the R5900 settings _FLT_LARGEST_EXPONENT_IS_NORMAL / _FLT_NO_DENORMALS (macro values reproduced locally; see floorf).
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
#define FLT_UWORD_IS_NAN(x) 0
#define FLT_UWORD_MAX 0x7fffffffL
#define FLT_LARGEST_EXP (FLT_UWORD_MAX>>23)
#define FLT_SMALLEST_EXP 1

static const float one = 1.0, Zero[] = {0.0, -0.0,};

float __ieee754_fmodf(float x, float y)
{
	__int32_t n,hx,hy,hz,ix,iy,sx,i;

	GET_FLOAT_WORD(hx,x);
	GET_FLOAT_WORD(hy,y);
	sx = hx&0x80000000;		/* sign of x */
	hx ^=sx;		/* |x| */
	hy &= 0x7fffffff;	/* |y| */

    /* purge off exception values */
	if(FLT_UWORD_IS_ZERO(hy)||
	   !FLT_UWORD_IS_FINITE(hx)||
	   FLT_UWORD_IS_NAN(hy))
	    return (x*y)/(x*y);
	if(hx<hy) return x;			/* |x|<|y| return x */
	if(hx==hy)
	    return Zero[(__uint32_t)sx>>31];	/* |x|=|y| return x*0*/

    /* Note: y cannot be zero if we reach here. */

    /* determine ix = ilogb(x) */
	if(FLT_UWORD_IS_SUBNORMAL(hx)) {	/* subnormal x */
	    for (ix = -126,i=(hx<<8); i>0; i<<=1) ix -=1;
	} else ix = (hx>>23)-127;

    /* determine iy = ilogb(y) */
	if(FLT_UWORD_IS_SUBNORMAL(hy)) {	/* subnormal y */
	    for (iy = -126,i=(hy<<8); i>=0; i<<=1) iy -=1;
	} else iy = (hy>>23)-127;

    /* set up {hx,lx}, {hy,ly} and align y to x */
	if(ix >= -126)
	    hx = 0x00800000|(0x007fffff&hx);
	else {		/* subnormal x, shift x to normal */
	    n = -126-ix;
	    hx = hx<<n;
	}
	if(iy >= -126)
	    hy = 0x00800000|(0x007fffff&hy);
	else {		/* subnormal y, shift y to normal */
	    n = -126-iy;
	    hy = hy<<n;
	}

    /* fix point fmod */
	n = ix - iy;
	while(n--) {
	    hz=hx-hy;
	    if(hz<0){hx = hx+hx;}
	    else {
	    	if(hz==0) 		/* return sign(x)*0 */
		    return Zero[(__uint32_t)sx>>31];
	    	hx = hz+hz;
	    }
	}
	hz=hx-hy;
	if(hz>=0) {hx=hz;}

    /* convert back to floating value and restore the sign */
	if(hx==0) 			/* return sign(x)*0 */
	    return Zero[(__uint32_t)sx>>31];
	while(hx<0x00800000) {		/* normalize x */
	    hx = hx+hx;
	    iy -= 1;
	}
	if(iy>= -126) {		/* normalize output */
	    hx = ((hx-0x00800000)|((iy+127)<<23));
	    SET_FLOAT_WORD(x,hx|sx);
	} else {		/* subnormal output */
	    /* If denormals are not supported, this code will generate a
	       zero representation.  */
	    n = -126 - iy;
	    hx >>= n;
	    SET_FLOAT_WORD(x,hx|sx);
	    x *= one;		/* create necessary signal */
	}
	return x;		/* exact output */
}
