#include "TimeoutException.h"

TimeoutException::TimeoutException(long timeout_ms)
    : timeout_ms(timeout_ms),
      message("Timeout of " + std::to_string(timeout_ms) + "ms reached") {}

const char* TimeoutException::what() const noexcept {
    return message.c_str();
}
