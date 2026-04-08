#pragma once
#include <stdint.h>

class TimerTD3
{
private:
    uint32_t tim;

public:
    void start();
    void stop();
    uint32_t getTime();
    bool TimerTD3::operator<(uint32_t dur);

};