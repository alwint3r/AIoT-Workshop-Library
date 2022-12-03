#ifndef DIGITAL_OUT_H_
#define DIGITAL_OUT_H_

#include <cstdint>

enum DigitalOutActiveEdge
{
    ACTIVE_LOW,
    ACTIVE_HIGH,
};

class DigitalOut
{
public:
    DigitalOut(uint8_t pin, DigitalOutActiveEdge edge = ACTIVE_HIGH);

    void begin();

    void on();
    void off();

    bool isOn();
    bool isOff();

private:
    uint8_t pin_;
    DigitalOutActiveEdge edge_;
    bool state_;
};

#endif // DIGITAL_OUT_H_