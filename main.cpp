#include <stdio.h>
#include <stdlib.h>
#include "timer_td3.h"
#include "timer_class.h"
#include "blinky_task.h"
bool LED1;
bool LED2;
bool LED3;
bool LED4;

Blinky blk1(LED1);
Blinky blk2(LED2);
Blinky blk3(LED3);
Blinky blk4(LED4);

int main()
{

    while( true )
    {
        blk1();
        blk2();
        blk3();
        blk4();
    }
    return 0;
}


/*
void process_function()
{
    system("dir c:\\Windows\\system32");
}

int main()
{
    TimerTD3 delay;

    delay.start();
    process_function();
    delay.stop();

//    if( delay > 100 )
//    {
        //xxxxxx
//    }

    printf("execution time: %d ms\n",delay.getTime());
}
*/
/*int main()
{
    uint32_t delay;

    timer_start(delay);
    process_function();
    timer_stop(delay);

    printf("execution time: %d ms\n",delay);

    if( delay > 500 )
        printf("Alert\n");

    return 0;
}*/