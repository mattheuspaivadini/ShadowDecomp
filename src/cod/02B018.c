/* asm/cod/02B018.s -> if.
 * Newlib 1.9.0 stdio/vfprintf.c static cvt (authentic source)
 * MATCHED. */
#include "newlib19_mprec.h"

#define _NO_LONGDBL
#define	ALT		0x001		/* alternate form */

extern char *_dtoa_r (struct _reent *, double, int, int, int *, int *, char **);
#define cvt func_0012B018

char *
cvt(data, value, ndigits, flags, sign, decpt, ch, length)
	struct _reent *data;
#ifdef _NO_LONGDBL
	double value;
#else
	_LONG_DOUBLE value;
#endif
	int ndigits, flags, *decpt, ch, *length;
	char *sign;
{
	int mode, dsgn;
	char *digits, *bp, *rve;
#ifdef _NO_LONGDBL
        union double_union tmp;
#else
        struct ldieee *ldptr;
#endif

	if (ch == 'f') {
		mode = 3;		/* ndigits after the decimal point */
	} else {
		/* To obtain ndigits after the decimal point for the 'e' 
		 * and 'E' formats, round to ndigits + 1 significant 
		 * figures.
		 */
		if (ch == 'e' || ch == 'E') {
			ndigits++;
		}
		mode = 2;		/* ndigits significant digits */
	}

#ifdef _NO_LONGDBL
        tmp.d = value;

	if (word0(tmp) & Sign_bit) { /* this will check for < 0 and -0.0 */
		value = -value;
		*sign = '-';
        } else
		*sign = '\000';

	digits = _dtoa_r(data, value, mode, ndigits, decpt, &dsgn, &rve);
#else /* !_NO_LONGDBL */
	ldptr = (struct ldieee *)&value;
	if (ldptr->sign) { /* this will check for < 0 and -0.0 */
		value = -value;
		*sign = '-';
        } else
		*sign = '\000';

	digits = _ldtoa_r(data, value, mode, ndigits, decpt, &dsgn, &rve);
#endif /* !_NO_LONGDBL */

	if ((ch != 'g' && ch != 'G') || flags & ALT) {	/* Print trailing zeros */
		bp = digits + ndigits;
		if (ch == 'f') {
			if (*digits == '0' && value)
				*decpt = -ndigits + 1;
			bp += *decpt;
		}
		if (value == 0)	/* kludge for __dtoa irregularity */
			rve = bp;
		while (rve < bp)
			*rve++ = '0';
	}
	*length = rve - digits;
	return (digits);
}
