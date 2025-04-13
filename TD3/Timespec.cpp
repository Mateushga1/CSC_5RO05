#include "Timespec.h"

time_t tv_sec;
long tv_nsec;

double timespec_to_ms(const timespec &time_ts)
{
    return (time_ts.tv_sec * MS_PER_SEC) + (time_ts.tv_nsec / NS_PER_MS);
}

timespec timespec_from_ms(double time_ms)
{
    timespec ts;
    ts.tv_sec = time_ms / MS_PER_SEC;
    ts.tv_nsec = std::lround((time_ms - ts.tv_sec * MS_PER_SEC) * NS_PER_MS);
    if (ts.tv_nsec < 0)
    {
        ts.tv_sec -= 1;
        ts.tv_nsec += NS_PER_SEC;
    }
    return ts;
}

timespec timespec_now()
{
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts;
}

timespec timespec_negate(const timespec &time_ts)
{
    timespec ts;
    ts.tv_sec = -time_ts.tv_sec - 1;
    ts.tv_nsec = -time_ts.tv_nsec + NS_PER_SEC;
    return ts;
}

timespec timespec_add(const timespec &time1_ts, const timespec &time2_ts)
{
    timespec ts;
    ts.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;
    ts.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
    if (ts.tv_nsec >= NS_PER_SEC)
    {
        ts.tv_sec += 1;
        ts.tv_nsec -= NS_PER_SEC;
    }
    return ts;
}

timespec timespec_subtract(const timespec &time1_ts, const timespec &time2_ts)
{
    timespec ts;
    ts.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;
    ts.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;
    if (ts.tv_nsec < 0)
    {
        ts.tv_sec -= 1;
        ts.tv_nsec += NS_PER_SEC;
    }
    return ts;
}

void timespec_wait(const timespec &delay_ts)
{
    timespec remaining = delay_ts;
    while (true)
    {
        int result = nanosleep(&remaining, &remaining);

        if (result == 0)
        {
            break;
        }
        if (errno == EINTR)
        {
            continue;
        }
        break;
    }
}

timespec operator-(const timespec &time_ts)
{
    return timespec_negate(time_ts);
}

timespec operator+(const timespec &time1_ts, const timespec &time2_ts)
{
    return timespec_add(time1_ts, time2_ts);
}

timespec operator-(const timespec &time1_ts, const timespec &time2_ts)
{
    return timespec_subtract(time1_ts, time2_ts);
}

timespec &operator+=(timespec &time_ts, const timespec &delay_ts)
{
    time_ts = timespec_add(time_ts, delay_ts);
    return time_ts;
}

timespec &operator-=(timespec &time_ts, const timespec &delay_ts)
{
    time_ts = timespec_subtract(time_ts, delay_ts);
    return time_ts;
}

bool operator==(const timespec &time1_ts, const timespec &time2_ts)
{
    return (time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec == time2_ts.tv_nsec);
}

bool operator!=(const timespec &time1_ts, const timespec &time2_ts)
{
    return (time1_ts.tv_sec != time2_ts.tv_sec) || (time1_ts.tv_nsec != time2_ts.tv_nsec);
}

bool operator<(const timespec &time1_ts, const timespec &time2_ts)
{
    return (time1_ts.tv_sec < time2_ts.tv_sec) || ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec < time2_ts.tv_nsec));
}

bool operator>(const timespec &time1_ts, const timespec &time2_ts)
{
    return (time1_ts.tv_sec > time2_ts.tv_sec) || ((time1_ts.tv_sec == time2_ts.tv_sec) && (time1_ts.tv_nsec > time2_ts.tv_nsec));
}

std::ostream &operator<<(std::ostream &os, const timespec &time_ts)
{
    os << time_ts.tv_sec << "s " << time_ts.tv_nsec << "ns";
    return os;
}
