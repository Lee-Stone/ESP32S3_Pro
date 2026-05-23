#include "XPT2046_Bitbang.h"


XPT2046_Bitbang::XPT2046_Bitbang(uint8_t mosiPin, uint8_t misoPin, uint8_t clkPin, uint8_t csPin, uint16_t screenWidth, uint16_t screenHeight) : 
    _mosiPin(mosiPin), _misoPin(misoPin), _clkPin(clkPin), _csPin(csPin), _screenWidth(screenWidth), _screenHeight(screenHeight) {
    cal = TouchCalibration{0, 4095, 0, 4095};
}

void XPT2046_Bitbang::begin() {
    pinMode(_mosiPin, OUTPUT);
    pinMode(_misoPin, INPUT);
    pinMode(_clkPin, OUTPUT);
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);
    digitalWrite(_clkPin, LOW);
}

void XPT2046_Bitbang::setCalibration(uint16_t xMin, uint16_t xMax, uint16_t yMin, uint16_t yMax) {
    cal = TouchCalibration{xMin, xMax, yMin, yMax};
}

void XPT2046_Bitbang::writeSPI(byte command) {
    for(int i = 7; i >= 0; i--) {
        digitalWrite(_mosiPin, command & (1 << i));
        digitalWrite(_clkPin, LOW);
        delayMicroseconds(DELAY);
        digitalWrite(_clkPin, HIGH);
        delayMicroseconds(DELAY);
    }
    digitalWrite(_mosiPin, LOW);
    digitalWrite(_clkPin, LOW);
}

uint16_t XPT2046_Bitbang::readSPI(byte command) {
    writeSPI(command);

    uint16_t result = 0;

    for(int i = 15; i >= 0; i--) {
        digitalWrite(_clkPin, HIGH);
        delayMicroseconds(DELAY);
        digitalWrite(_clkPin, LOW);
        delayMicroseconds(DELAY);
        result |= (digitalRead(_misoPin) << i);
    }

    return result >> 4;
}

TouchPoint XPT2046_Bitbang::getTouch() {
    digitalWrite(_csPin, LOW);

    uint16_t z1 = readSPI(CMD_READ_Z1);
    uint16_t z = z1 + 4095;
    uint16_t z2 = readSPI(CMD_READ_Z2);
    z -= z2;

    if(z < 100) {
        return TouchPoint{0, 0, 0, 0, 0};
    }

    uint16_t xRaw = readSPI(CMD_READ_X);
    uint16_t yRaw = readSPI(CMD_READ_Y & ~((byte)1));
    digitalWrite(_csPin, HIGH);
    // Rotate and map
    uint16_t x = map(xRaw, cal.xMin, cal.xMax, 0, _screenWidth);
    uint16_t y = map(yRaw, cal.yMin, cal.yMax, 0, _screenHeight);

    if (x > _screenWidth){
        x = _screenWidth;
    }
    if (x < 0) {
        x = 0;
    }
    if (y > _screenHeight) {
        y = _screenHeight;
    }
    if (y < 0) {
        y = 0;
    }
    return TouchPoint{x, y, xRaw, yRaw, z};
}
