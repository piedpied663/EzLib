#include <EzLib.h>

#define R1 1000
#define R2 2200
#define R3 2700
#define R4 3300
#define R5 3900
#define R6 4700

#define ANALOG_BOUTON_0 R2
#define ANALOG_BOUTON_1 R3
#define ANALOG_BOUTON_2 R4
#define ANALOG_BOUTON_3 R5
#define ANALOG_BOUTON_4 R6

using Pup = EzDigitPullUp;
using Pdn = EzDigitPullDown;
using Abtn = EzAnalogButton;

Pup btn_pullUp(3);
Pdn btn_pulldown(2);
Abtn btn_analog_0(A0, R1, R2);
Abtn btn_analog_1(A0, R1, R3);
Abtn btn_analog_2(A0, R1, R4);
Abtn btn_analog_3(A0, R1, R5);
Abtn btn_analog_4(A0, R1, R6);

void setup()
{
    Serial.begin(115200);
    btn_pullUp.begin();
    btn_pulldown.begin();
    btn_analog_0.begin();
    btn_analog_1.begin();
    btn_analog_2.begin();
    btn_analog_3.begin();
    btn_analog_4.begin();
}

void loopPullUp()
{
    if (btn_pullUp.isPressed())
    {
        Serial.println("btn_pullUp Pressed");
    }
    else if (btn_pullUp.isLongPressed())
    {
        Serial.println("btn_pullUp Long Pressed");
    }
    else if (btn_pullUp.isReleased())
    {
        Serial.println("btn_pullUp Released");
    }
}

void loopPullDown()
{
    if (btn_pulldown.isPressed())
    {
        Serial.println("btn_pulldown Pressed");
    }
    else if (btn_pulldown.isLongPressed())
    {
        Serial.println("btn_pulldown Long Pressed");
    }
    else if (btn_pulldown.isReleased())
    {
        Serial.println("btn_pulldown Released");
    }
}

void loopAnalog()
{
    if (btn_analog_0.isPressed())
    {
        Serial.println(F("btn_analog 0 Pressed"));
    }
    
    if (btn_analog_1.isPressed())
    {
        Serial.println(F("btn_analog 1 Pressed"));
    }

    
    if (btn_analog_2.isPressed())
    {
        Serial.println(F("btn_analog 2 Pressed"));
    }

    
    if (btn_analog_3.isPressed())
    {
        Serial.println(F("btn_analog 3 Pressed"));
    }

    
    if (btn_analog_4.isPressed())
    {
        Serial.println(F("btn_analog 4 Pressed"));
    }
}

void loop()
{
    loopPullUp();
    loopPullDown();
    loopAnalog();
}
