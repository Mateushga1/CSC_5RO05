#include <iostream>
#include "Timespec.h"

void test_timespec_to_ms()
{
    std::cout << std::endl
              << "Test timespec_to_ms" << std::endl;

    timespec ts1 = {1, 500000000};
    std::cout << "Test ts1: " << ts1 << std::endl;

    timespec ts2 = {0, 1000000};
    std::cout << "Test ts2: " << ts2 << std::endl;

    timespec ts3 = {2, 0};
    std::cout << "Test ts3: " << ts3 << std::endl;
}

void test_timespec_from_ms()
{
    std::cout << std::endl
              << "Test timespec_from_ms" << std::endl;

    double ms1 = 1500.0;
    timespec ts1 = timespec_from_ms(ms1);
    std::cout << "Test ms1: " << ts1 << std::endl;

    double ms2 = 1.0;
    timespec ts2 = timespec_from_ms(ms2);
    std::cout << "Test ms2: " << ts2 << std::endl;

    double ms3 = 2000.0;
    timespec ts3 = timespec_from_ms(ms3);
    std::cout << "Test ms3: " << ts3 << std::endl;
}

void test_timespec_now()
{
    std::cout << std::endl
              << "Test timespec_now" << std::endl;

    timespec ts = timespec_now();
    std::cout << "Test ts: " << ts << std::endl;
}

void test_timespec_negate()
{
    std::cout << std::endl
              << "Test timespec_negate" << std::endl;

    timespec ts1 = {1, 500000000};
    timespec ts2 = timespec_negate(ts1);
    std::cout << "Test ts2: " << ts2 << std::endl;

    timespec ts3 = {0, 1000000};
    timespec ts4 = timespec_negate(ts3);
    std::cout << "Test ts4: " << ts4 << std::endl;

    timespec ts5 = {2, 0};
    timespec ts6 = timespec_negate(ts5);
    std::cout << "Test ts6: " << ts6 << std::endl;
}

void test_timespec_add()
{
    std::cout << std::endl
              << "Test timespec_add" << std::endl;

    timespec ts1 = {1, 500000000};
    timespec ts2 = {0, 1000000};
    timespec ts3 = timespec_add(ts1, ts2);
    std::cout << "Test ts3: " << ts3 << std::endl;

    timespec ts4 = {0, 1000000};
    timespec ts5 = {2, 0};
    timespec ts6 = timespec_add(ts4, ts5);
    std::cout << "Test ts6: " << ts6 << std::endl;

    timespec ts7 = {2, 0};
    timespec ts8 = {1, 500000000};
    timespec ts9 = timespec_add(ts7, ts8);
    std::cout << "Test ts9: " << ts9 << std::endl;
}

void test_timespec_subtract()
{
    std::cout << std::endl
              << "Test timespec_subtract" << std::endl;

    timespec ts1 = {1, 500000000};
    timespec ts2 = {0, 1000000};
    timespec ts3 = timespec_subtract(ts1, ts2);
    std::cout << "Test ts3: " << ts3 << std::endl;

    timespec ts4 = {0, 1000000};
    timespec ts5 = {2, 0};
    timespec ts6 = timespec_subtract(ts4, ts5);
    std::cout << "Test ts6: " << ts6 << std::endl;

    timespec ts7 = {2, 0};
    timespec ts8 = {1, 500000000};
    timespec ts9 = timespec_subtract(ts7, ts8);
    std::cout << "Test ts9: " << ts9 << std::endl;
}

void test_timespec_wait()
{
    std::cout << std::endl
              << "Test timespec_wait" << std::endl;

    timespec ts = {1, 0}; 
    timespec_wait(ts);

    std::cout << "Timespec wait done" << std::endl;
}

int main()
{
    test_timespec_to_ms();
    test_timespec_from_ms();
    test_timespec_now();
    test_timespec_negate();
    test_timespec_add();
    test_timespec_subtract();
    test_timespec_wait();
    return 0;
}
