#ifndef TIMEOUTEXCEPTION_H
#define TIMEOUTEXCEPTION_H

#include <exception>

class TimeoutException : public std::exception
{
private:
    const long timeout_ms;

public:
    TimeoutException(long timeout_ms);
    const char* what() const throw();
};

#endif
