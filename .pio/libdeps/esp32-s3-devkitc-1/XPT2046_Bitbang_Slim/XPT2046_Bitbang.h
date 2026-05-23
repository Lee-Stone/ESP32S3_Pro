#ifndef XPT2046_Bitbang_h
#define XPT2046_Bitbang_h

#include "Arduino.h"

#define CMD_READ_X   0x91 // Command for XPT2046 to read X position
#define CMD_READ_Y   0xD1 // Command for XPT2046 to read Y position
#define CMD_READ_Z1  0xB1 // Command for XPT2046 to read Z1 position
#define CMD_READ_Z2  0xC1 // Command for XPT2046 to read Z2 position

#define DELAY 5

struct TouchPoint {
    uint16_t x;
    uint16_t y;
    uint16_t xRaw;
    uint16_t yRaw;
    uint16_t zRaw;
};

struct TouchCalibration {
    uint16_t xMin;
    uint16_t xMax;
    uint16_t yMin;
    uint16_t yMax;
};

class XPT2046_Bitbang {
    public:
        XPT2046_Bitbang(uint8_t mosiPin, uint8_t misoPin, uint8_t clkPin, uint8_t csPin, uint16_t screenWidth = 320, uint16_t screenHeight = 240);
        void begin();
        TouchPoint getTouch();
        void setCalibration(uint16_t xMin, uint16_t xMax, uint16_t yMin, uint16_t yMax);

    private:
        uint8_t _mosiPin;
        uint8_t _misoPin;
        uint8_t _clkPin;
        uint8_t _csPin;
        uint16_t _screenWidth;
        uint16_t _screenHeight;
        TouchCalibration cal;
        void writeSPI(byte command);
        uint16_t readSPI(byte command);
};

#endif
