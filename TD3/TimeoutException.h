#ifndef TIMEOUTEXCEPTION_H
#define TIMEOUTEXCEPTION_H

#include <exception>
#include <string>

class TimeoutException : public std::exception {
private:
    long timeout_ms;
    std::string message;

public:
    explicit TimeoutException(long timeout_ms);
    const char* what() const noexcept override;
};

#endif
