#pragma once
#include <Arduino.h>
namespace ez
{
    class Pin
    {
    protected:
        inline Pin(uint8_t pin) : pin_(pin) {}
        uint8_t pin_;
        bool begin_(uint8_t inputMode)
        {
            pinMode(this->pin_, inputMode);
#ifdef EXTRA_SETUP
            Serial.print(F("Pin: "));
            Serial.println(this->pin_);
            Serial.print(F("Mode: "));
            Serial.println(inputMode == INPUT_PULLUP ? F("INPUT_PULLUP") : F("INPUT"));
#endif
            return true;
        }

    private:
        Pin(const Pin &) = delete;
        Pin &operator=(const Pin &) = delete;
    };

    class DebouncedPin : public Pin
    {
    private:
        int _last_state;
        bool _has_changed;
        unsigned long _last_debounce;

    protected:
        int _state; 
        DebouncedPin(uint8_t pin, uint8_t initState) : Pin(pin), _last_state(initState), _has_changed(false) {}

        inline bool _begin(uint8_t mode)
        {
            return this->begin_(mode);
        }
        inline void _read()
        {
            // bool change = false;

            if (this->_last_state != this->_state)
            {
                if (millis() - this->_last_debounce >= 50)
                {
                    this->_last_debounce = millis();
                    this->_has_changed = true;
                }

                this->_last_state = this->_state;
            }
        }
        inline int State()
        {
            return this->_state;    
        }
        inline void setState(int state)
        {
            this->_state = state;
        }


        inline bool _hasChanged()      {
            if(this->_has_changed)
            {
                this->_has_changed = false;
                return true;
            }
            return false;
        }

    private:
        DebouncedPin(const DebouncedPin &) = delete;
        DebouncedPin &operator=(const DebouncedPin &) = delete;
    };

    class ClickerPin : public DebouncedPin
    {
    protected:
        ClickerPin(uint8_t pin, uint8_t initState) : DebouncedPin(pin, initState) {}

    private:
        ClickerPin(const ClickerPin &cpy) = delete;
        ClickerPin &operator=(const ClickerPin &) = delete;
    };

}