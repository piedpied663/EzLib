#pragma once

#include <Arduino.h>

namespace ez
{
    #define ADC_MAX 1023
    #define VCC_IN 5

    class Circuit
    {
    private:
        Circuit() = delete;
        Circuit(const Circuit &) = delete;
        Circuit operator=(const Circuit &) = delete;
    };

    class DigitalCircuitPullUp : private Circuit
    {
    public:
        enum
        {
            INPUT_MODE = INPUT_PULLUP,
            READ_MODE = 'd',
            STATE_HIGH = LOW,
            STATE_LOW = HIGH
        };

    private:
        DigitalCircuitPullUp() = delete;
        DigitalCircuitPullUp(const DigitalCircuitPullUp &) = delete;
        DigitalCircuitPullUp &operator=(const DigitalCircuitPullUp &) = delete;
    };

    class DigitalCircuitPullDown : private Circuit
    {
    public:
        enum
        {
            INPUT_MODE = INPUT,
            STATE_HIGH = HIGH,
            STATE_LOW = LOW
        };

    private:
        DigitalCircuitPullDown() = delete;
        DigitalCircuitPullDown(const DigitalCircuitPullDown &) = delete;
        DigitalCircuitPullDown &operator=(const DigitalCircuitPullDown &) = delete;
    };

    class AnalogCircuit : private Circuit
    {
    public:
        enum
        {
            INPUT_MODE = INPUT,
            STATE_HIGH = ADC_MAX,
            STATE_LOW = 0,
            VCC = VCC_IN
        };

    private:
        AnalogCircuit() = delete;
        AnalogCircuit(const AnalogCircuit &) = delete;
        AnalogCircuit &operator=(const AnalogCircuit &) = delete;
    };
}