#pragma once

#include <Arduino.h>
#include "Circuit.h"
#include "Pin.hpp"

namespace ez
{

    template <typename Circuit, typename Pin>
    class DigitalButtonBase : public Pin
    {
    private:
        DigitalButtonBase() = delete;
        DigitalButtonBase(const DigitalButtonBase &) = delete;
        unsigned long _pressStartTime;
        bool _isPressed;
        bool _isReleased;
        bool _isLongPressed;
    public:
        DigitalButtonBase(uint8_t pin) : Pin(pin, Circuit::STATE_LOW) {}

    public:
        void begin()
        {
            this->_begin(Circuit::INPUT_MODE);
        }

        void readDigital()
        {
            this->setState(digitalRead(this->pin_));
            
            DebouncedPin::_read();

            if (this->_hasChanged())
            {
                _pressStartTime = millis();
                int currentState = this->State();

                if (currentState == Circuit::STATE_LOW)
                {
                    // this->_isPressed = false;
                    _isReleased = true;
                }
                else if (currentState == Circuit::STATE_HIGH)
                {
                    // this->_isReleased = false;
                    if (millis() - _pressStartTime >= 500)
                    {
                        _isLongPressed = true;
                        _pressStartTime = 0;
                    }
                    else
                    {
                        _isPressed = true;
                    }
                }
            }
        }

    public:
        // accessors
        bool isPressed()
        {
            this->readDigital();
            if (_isPressed)
            {
                _isPressed = false;
                return true;
            }
            return false;
        }
        bool isReleased()
        {

            if (this->_isReleased)
            {
                this->_isReleased = false;
                return this->_state == Circuit::STATE_LOW;
            }
            return false;
        }
        bool isLongPressed()
        {
            if (this->_isLongPressed)
            {
                this->_isLongPressed = false;
                return true;
            }

            return false;
        }
    };

    template <typename Circuit, typename Pin>
    class AnalogButtonBase : public Pin
    {
    private:
        AnalogButtonBase() = delete;
        AnalogButtonBase(const AnalogButtonBase &) = delete;

    private:
        float _last_tension = 0.0f;
        float _current_tension = 0.0f;
        int _r1;
        int _rx;
        bool _isPressing = false;
        bool _isPressed = false;

        float tension()
        {
            return (float)this->_state * Circuit::VCC / Circuit::STATE_HIGH;
        }
        float Vout()
        {
            float _vcc = Circuit::VCC;

            return (float)(_vcc - (_rx * (_vcc / (_r1 + _rx))));
        }
        bool egal(float x, float y, float precision)
        {
            return abs(x - y) < precision;
        }

    public:
        AnalogButtonBase(uint8_t pin) : Pin(pin, Circuit::STATE_LOW) {}
        AnalogButtonBase(uint8_t pin, int r1, int rx) : Pin(pin, Circuit::STATE_LOW), _r1(r1), _rx(rx) {}

    public:
        void begin()
        {
            this->_begin(Circuit::INPUT_MODE);
        }

    private:
        void readAnalog()
        {
            this->setState(analogRead(this->pin_));
            DebouncedPin::_read();

            if (this->_hasChanged())
            {
                if (this->State() > Circuit::STATE_LOW)
                {
                    _isPressing = true;
                }
            }
        }

        void readTension()
        {
            if (_isPressing)
            {
                _isPressing = false;
                _current_tension = tension();
                if (_current_tension > _last_tension)
                {
                    if (egal(_current_tension, Vout(), .01f))
                    {
                        _isPressed = true;
                    }
                }
            }
        }

    public:
        // accessors
        bool isPressed()
        {
            this->readAnalog();
            this->readTension();
            if (this->_isPressed)
            {
                this->_isPressed = false;
                return true;
            }
            return false;
        }
    };
}