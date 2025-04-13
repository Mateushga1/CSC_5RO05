#ifndef TIMESPEC_H
#define TIMESPEC_H

#include <iostream>
#include <time.h>
#include <cmath>

constexpr double NS_PER_SEC = 1.0e9;
constexpr double MS_PER_SEC = 1.0e3;
constexpr double NS_PER_MS = NS_PER_SEC / MS_PER_SEC;

double timespec_to_ms(const timespec &time_ts);
timespec timespec_from_ms(double time_ms);

timespec timespec_now();
timespec timespec_negate(const timespec &time_ts);

timespec timespec_add(const timespec &time1_ts, const timespec &time2_ts);
timespec timespec_subtract(const timespec &time1_ts, const timespec &time2_ts);

void timespec_wait(const timespec &delay_ts);

timespec operator-(const timespec &time_ts);
timespec operator+(const timespec &time1_ts, const timespec &time2_ts);
timespec operator-(const timespec &time1_ts, const timespec &time2_ts);
timespec &operator+=(timespec &time_ts, const timespec &delay_ts);
timespec &operator-=(timespec &time_ts, const timespec &delay_ts);
bool operator==(const timespec &time1_ts, const timespec &time2_ts);
bool operator!=(const timespec &time1_ts, const timespec &time2_ts);
bool operator<(const timespec &time1_ts, const timespec &time2_ts);
bool operator>(const timespec &time1_ts, const timespec &time2_ts);
std::ostream &operator<<(std::ostream &os, const timespec &time_ts);

#endif
