/* KERNEL.XFF @ 0x000868 (112 B) - iosGetClockSecond
 * Evidence: for a valid sceCdCLOCK (stat == 0) fills a stack struct tm (second, minute, hour, day, month - 1, year - 1900, wday/yday/isdst = 0) and returns mktime(&tm); otherwise 0. The fields are used as stored (no BCD conversion).
 */
struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};
typedef struct {
    unsigned char stat;
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char pad;
    unsigned char day;
    unsigned char month;
    unsigned char year;
} sceCdCLOCK;
long mktime(struct tm *tm);

long iosGetClockSecond(sceCdCLOCK *c) {
    struct tm tm;

    if (c->stat != 0) {
        return 0;
    }
    tm.tm_sec = c->second;
    tm.tm_min = c->minute;
    tm.tm_hour = c->hour;
    tm.tm_mday = c->day;
    tm.tm_mon = c->month - 1;
    tm.tm_year = c->year - 1900;
    tm.tm_wday = 0;
    tm.tm_yday = 0;
    tm.tm_isdst = 0;
    return mktime(&tm);
}
