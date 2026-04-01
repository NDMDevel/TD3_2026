#include "timer_class.h"
#include <chrono>

using namespace std::chrono_literals;

inline uint32_t sysTick32_ms()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
inline uint32_t sysTick32_us()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void TimerTD3::start()
{
    tim = ~sysTick32_ms() + (uint32_t)1;
}

void TimerTD3::stop()
{
    tim = tim + sysTick32_ms();
}

uint32_t TimerTD3::getTime()
{
    return tim;
}

bool TimerTD3::operator<(uint32_t dur)
{
    return tim < dur;
}