#include <Arduino.h>

#ifndef LED_AND_KEY_H
#define LED_AND_KEY_H

// led&key commands
#define CMD_MODE_WRITE 0x40
#define CMD_MODE_WRITE_NO_INCREMENT 0x44
#define CMD_MODE_READ 0x42
#define CMD_MODE_READ_NO_INCREMENT 0x46

#define CMD_DISPLAY_OFF 0x80
#define CMD_DISPLAY_ON 0x8f
#define BRIGHTNESS_CMD_MASK 0xf8
// end commands

// led&key addresses
#define ADDR_BASE 0xc0

#define ADDR_LED_0 ADDR_BASE | 0x1
#define ADDR_LED_1 ADDR_BASE | 0x3
#define ADDR_LED_2 ADDR_BASE | 0x5
#define ADDR_LED_3 ADDR_BASE | 0x7
#define ADDR_LED_4 ADDR_BASE | 0x9
#define ADDR_LED_5 ADDR_BASE | 0xb
#define ADDR_LED_6 ADDR_BASE | 0xd
#define ADDR_LED_7 ADDR_BASE | 0xf

#define ADDR_DISP_0 ADDR_BASE
#define ADDR_DISP_1 ADDR_BASE | 0x2
#define ADDR_DISP_2 ADDR_BASE | 0x4
#define ADDR_DISP_3 ADDR_BASE | 0x6
#define ADDR_DISP_4 ADDR_BASE | 0x8
#define ADDR_DISP_5 ADDR_BASE | 0xa
#define ADDR_DISP_6 ADDR_BASE | 0xc
#define ADDR_DISP_7 ADDR_BASE | 0xe
// end addresses

class LedKey
{
private:
    int pinStb;
    int pinClk;
    int pinDio;

public:
    LedKey(int stb, int clk, int dio);

    void init();

    // disp: the 7-seg-disp 0-7, data: the state of the leds
    void setDisp(uint8_t disp, uint8_t data);

    // led: 0-7, state: 0,1
    void setLed(uint8_t led, uint8_t state);

    // set brightness: 0-7
    void setBrightness(uint8_t brightness);

    // set all registers; 0x00 -> clear
    void setAll(uint8_t value);

    uint8_t readValue(uint8_t btn);

    // bits 0-7: btn 0-7
    uint8_t readValue();

    void sendValues(uint8_t value1, uint8_t value2);
    void sendValues(uint8_t value1);
    void sendValues(uint8_t values[], int len);
};

#endif // LED_AND_KEY_H