#pragma once
#include "timer_class.h"

class Blinky
{
private:
    bool &led;
    int st;
    TimerTD3 tim;
public:
    Blinky(bool &led_pin) : led(led_pin)
    {

    }
    void operator()()
    {
        if( st == 0 )
        {
            tim.start();
            st = 1;
            return;
        }
        if( st == 1 )
        {
            if( tim < 100 )
                return;
            led = !led;
            st = 0;
            return;
        }
    }
};