#include "Timer.h"

Timer::Timer()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = Timer::call_callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void *)this;

    timer_create(CLOCK_REALTIME, &sev, &tid);
}

Timer::~Timer()
{
    timer_delete(tid);
}

void Timer::start(timespec duration, bool isPeriodic)
{
    itimerspec its{{0, 0}, {0, 0}};
    its.it_value = duration;
    if (isPeriodic)
        its.it_interval = duration;
    timer_settime(tid, 0, &its, nullptr);
}

void Timer::start_ms(double duration_ms, bool isPeriodic)
{
    timespec duration = timespec_from_ms(duration_ms);
    start(duration, isPeriodic);
}

void Timer::stop()
{
    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    timer_settime(tid, 0, &its, nullptr);
}

void Timer::call_callback(int, siginfo_t *si, void *)
{
    Timer *timer = (Timer *)si->si_value.sival_ptr;
    timer->callback();
}
