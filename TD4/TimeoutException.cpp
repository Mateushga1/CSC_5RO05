#include "TimeoutException.h"
#include <string>

TimeoutException::TimeoutException(long timeout_ms) : timeout_ms(timeout_ms) {}

const char* TimeoutException::what() const throw()
{
    std::string message = "Timeout of " + std::to_string(timeout_ms) + "ms reached";
    return message.c_str();
}
