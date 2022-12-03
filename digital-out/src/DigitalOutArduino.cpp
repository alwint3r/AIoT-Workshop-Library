#include "DigitalOut.h"
#include <Arduino.h>

DigitalOut::DigitalOut(uint8_t pin, DigitalOutActiveEdge edge): pin_(pin), edge_(edge)
{
}

void DigitalOut::begin()
{
    pinMode(pin_, OUTPUT);
    off();
}

void DigitalOut::off()
{
    auto logic = edge_ == ACTIVE_HIGH ? LOW : HIGH;
    digitalWrite(pin_, logic);
    state_ = false;
}

void DigitalOut::on()
{
    auto logic = edge_ == ACTIVE_HIGH ? HIGH : LOW;
    digitalWrite(pin_, logic);
    state_ = true;
}

bool DigitalOut::isOff()
{
    return state_ == false;
}

bool DigitalOut::isOn()
{
    return state_ == true;
}
