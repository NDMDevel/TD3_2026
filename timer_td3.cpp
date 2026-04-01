#include "timer_td3.h"
#include <chrono>

inline uint32_t sysTick32_ms()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
inline uint32_t sysTick32_us()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void timer_start(uint32_t &tim)
{
    tim = ~sysTick32_ms() + (uint32_t)1;
}

void timer_stop(uint32_t &tim)
{
    tim = tim + sysTick32_ms();
}
