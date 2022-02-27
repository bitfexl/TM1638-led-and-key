#include "ledAndKey.h"

LedKey::LedKey(int stb, int clk, int dio)
{
    pinStb = stb;
    pinClk = clk;
    pinDio = dio;
}

void LedKey::init()
{
    // setup pins
    pinMode(pinStb, OUTPUT);
    pinMode(pinClk, OUTPUT);
    pinMode(pinDio, OUTPUT);
    digitalWrite(pinStb, HIGH);

    // init led&key
    sendValues(CMD_MODE_WRITE_NO_INCREMENT);
    sendValues(CMD_DISPLAY_OFF);
    setAll(0x00);
    setBrightness(7);
}

void LedKey::setDisp(uint8_t disp, uint8_t data)
{
    uint8_t addr = ADDR_BASE | (disp * 2);
    sendValues(addr, data);
}

void LedKey::setLed(uint8_t led, uint8_t state)
{
    uint8_t addr = ADDR_BASE | (led * 2 + 1);
    sendValues(addr, state);
}

void LedKey::setBrightness(uint8_t brightness)
{
    brightness = brightness | BRIGHTNESS_CMD_MASK;
    sendValues(CMD_DISPLAY_ON & brightness);
}

void LedKey::setAll(uint8_t value)
{
    for (int i = 0; i < 16; i++)
    {
        sendValues(ADDR_BASE | i, value);
    }
}

uint8_t LedKey::readValue(uint8_t btn)
{
    return (readValue() >> btn) & 1;
}

uint8_t LedKey::readValue()
{
    digitalWrite(pinStb, LOW);
    shiftOut(pinDio, pinClk, LSBFIRST, CMD_MODE_READ);
    pinMode(pinDio, INPUT);

    uint8_t value = 0;
    for (int i = 0; i < 4; i++)
    {
        value |= shiftIn(pinDio, pinClk, LSBFIRST) << i;
    }

    digitalWrite(pinStb, HIGH);
    pinMode(pinDio, OUTPUT);
    return value;
}

void LedKey::sendValues(uint8_t value1, uint8_t value2)
{
    uint8_t values[] = {value1, value2};
    sendValues(values, 2);
}

void LedKey::sendValues(uint8_t value1)
{
    uint8_t values[] = {value1};
    sendValues(values, 1);
}

void LedKey::sendValues(uint8_t values[], int len)
{
    digitalWrite(pinStb, LOW);
    for (int i = 0; i < len; i++)
    {
        shiftOut(pinDio, pinClk, LSBFIRST, values[i]);
    }
    digitalWrite(pinStb, HIGH);
}