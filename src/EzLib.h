#pragma once
#define EXTRA_SETUP

#include <Arduino.h>
#include <Button.h>

using EzDigitPullUp = ez::DigitalButtonBase<ez::DigitalCircuitPullUp, ez::ClickerPin>;
using EzDigitPullDown = ez::DigitalButtonBase<ez::DigitalCircuitPullDown, ez::ClickerPin>;
using EzAnalogButton = ez::AnalogButtonBase<ez::AnalogCircuit, ez::ClickerPin>;