/* asm/cod/02FA00.s -> while.
 * Newlib 1.9.0 libm/math/s_isnan.c isnan (authentic source)
 * MATCHED. */
typedef int __int32_t;
typedef unsigned int __uint32_t;

/* newlib/libm/common/fdlibm.h (__IEEE_LITTLE_ENDIAN) */
typedef union 
{
  double value;
  struct 
  {
    __uint32_t lsw;
    __uint32_t msw;
  } parts;
} ieee_double_shape_type;

/* Get two 32 bit ints from a double.  */

#define EXTRACT_WORDS(ix0,ix1,d)				do {								  ieee_double_shape_type ew_u;					  ew_u.value = (d);						  (ix0) = ew_u.parts.msw;					  (ix1) = ew_u.parts.lsw;					} while (0)

int isnan(double x)
{
	__int32_t hx,lx;
	EXTRACT_WORDS(hx,lx,x);
	hx &= 0x7fffffff;
	hx |= (__uint32_t)(lx|(-lx))>>31;	
	hx = 0x7ff00000 - hx;
	return (int)(((__uint32_t)(hx))>>31);
}
