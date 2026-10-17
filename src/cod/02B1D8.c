/* asm/cod/02B1D8.s -> if.
 * Newlib 1.9.0 stdio/vfprintf.c static exponent (BSD expbuf[MAXEXP]) (authentic source)
 * MATCHED. */
#define	to_char(n)	((n) + '0')
#define exponent func_0012B1D8
#define	MAXEXP		308

int
exponent(p0, exp, fmtch)
	char *p0;
	int exp, fmtch;
{
	register char *p, *t;
	char expbuf[MAXEXP];

	p = p0;
	*p++ = fmtch;
	if (exp < 0) {
		exp = -exp;
		*p++ = '-';
	}
	else
		*p++ = '+';
	t = expbuf + MAXEXP;
	if (exp > 9) {
		do {
			*--t = to_char(exp % 10);
		} while ((exp /= 10) > 9);
		*--t = to_char(exp);
		for (; t < expbuf + MAXEXP; *p++ = *t++);
	}
	else {
		*p++ = '0';
		*p++ = to_char(exp);
	}
	return (p - p0);
}
