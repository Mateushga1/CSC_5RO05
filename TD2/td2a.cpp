#include <iostream>
#include <time.h>
#include <signal.h>

void myHandler(int, siginfo_t *si, void *)
{
    int *p_counter = (int *)si->si_value.sival_ptr;
    std::cout << "Counter: " << (*p_counter += 1) << std::endl;
}

int main()
{

    int counter = 0;
    int *myData = &counter;

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = myHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void *)myData;

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);
    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 500000000;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 500000000;
    timer_settime(tid, 0, &its, nullptr);

    while (counter < 15)
    {
    }

    timer_delete(tid);

    return 0;
}
