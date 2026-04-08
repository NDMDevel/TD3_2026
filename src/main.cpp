#include <Arduino.h>
#include "Timers.h"

//0- preferir codigo declarativo a codigo imperativo
//   (declarativo, dice que hace)
//   (imperativo, dice como lo hace)

//1- hacer interfaces (funciones) faciles de usar CORRECTAMENTE
//   y dificilies de INCORRECTAMENTE

//2- mostrar gradualmente los detalles de codigo

//3- crear funciones de soporte (que resuelven cosas puntuales/acotadas)

void toggle_pin(int pin)
{
    digitalWrite(pin, !digitalRead(pin) );
}

Tim32_ms timer;

//C
//enum Blinky_st
//{
//    shutdown = 0,
//    toggle   = 1,
//    waiting  = 2
//};

//C++
enum class Blinky_st : uint8_t
{
    shutdown = 0,
    toggle   = 1,
    waiting  = 2
};

enum class Modbus_st
{
    shutdown = 0,
    toggle   = 1,
    waiting  = 2
};

Blinky_st st;

void blinky()
{
    if( st == Blinky_st::shutdown )
    {
        return;
    }
    if( st == Blinky_st::toggle )
    {
        toggle_pin(2);
        timer.start();
        st = Blinky_st::waiting;
        return;
    }
    if( st == Blinky_st::waiting )
    {
        if( timer < 100ms )
            return;
        st = Blinky_st::toggle;
        return;
    }
}

void setup()
{
    //pin 2 as output (assume LED)
    pinMode(2,OUTPUT);

    st = Blinky_st::toggle;
}

void loop()
{
    blinky();
}
