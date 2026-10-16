/* STATUS (14, 2026-10-16): NON_MATCHING. best score 17 [cc=296].
 * Newlib strtoul.c from the authentic source; same residual class as 0295C8 (loop rotation/scheduling, 142 vs 140 insns). Confirmed details: ULONG_MAX division runs __udivdi3 first then __umoddi3 (source order), (unsigned long)base kept in s7 for __muldi3, neg spilled to 0x04(sp), any in s0.
 * The original .s stays in the build (asm/cod/030B18.s); this C
 * draft (14) is kept for the record. */
struct S030B18_reent {
    int _errno;                 /* 0x00 */
};

#define _U 0x01
#define _L 0x02
#define _N 0x04
#define _S 0x08

extern const unsigned char _ctype_[0x101];

#define isspace_(c) (((_ctype_ + 1)[(int)(c)] & _S) != 0)
#define isdigit_(c) (((_ctype_ + 1)[(int)(c)] & _N) != 0)
#define isalpha_(c) (((_ctype_ + 1)[(int)(c)] & (_U | _L)) != 0)
#define isupper_(c) (((_ctype_ + 1)[(int)(c)] & _U) != 0)

#define ULONG_MAX_ 0xFFFFFFFFFFFFFFFFUL
#define ERANGE_    34

unsigned long _strtoul_r(struct S030B18_reent *rptr, const char *nptr,
                         char **endptr, int base)
{
    register const char *s = nptr;
    register unsigned long acc;
    register int c;
    register unsigned long cutoff;
    register int neg = 0, any, cutlim;

    do {
        c = *s++;
    } while (isspace_(c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;

    cutoff = (unsigned long)ULONG_MAX_ / (unsigned long)base;
    cutlim = (unsigned long)ULONG_MAX_ % (unsigned long)base;
    for (acc = 0, any = 0;; c = *s++) {
        if (isdigit_(c))
            c -= '0';
        else if (isalpha_(c))
            c -= isupper_(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = ULONG_MAX_;
        rptr->_errno = ERANGE_;
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *)(any ? (char *)s - 1 : nptr);
    return (acc);
}
