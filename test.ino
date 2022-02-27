#include "src/ledAndKey/ledAndKey.h"
#include "src/ledAndKey/segDispCodes.h"

// pin definitions
#define PIN_STB 7
#define PIN_CLK 6
#define PIN_DIO 5

uint8_t dispNumbers[] = {DISP_0, DISP_1, DISP_2, DISP_3, DISP_4, DISP_5, DISP_6, DISP_7, DISP_8, DISP_9, DISP_A, DISP_b, DISP_c, DISP_d, DISP_E, DISP_F};

LedKey ledKey(PIN_STB, PIN_CLK, PIN_DIO);

uint32_t number = 0;

void setup()
{
    ledKey.init();
}

void loop()
{
    uint8_t value = ledKey.readValue();
    for (int i = 0; i < 8; i++)
    {
        ledKey.setLed(i, (value >> i) & 1);
    }

    writeNum(number);
    number++;
}

void writeNum(uint32_t num)
{
    for (int i = 0; i < 8; i++)
    {
        ledKey.setDisp(7 - i, dispNumbers[num % 10]);
        num /= 10;
    }
}