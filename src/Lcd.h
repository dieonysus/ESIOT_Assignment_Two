#ifndef __LCD__
#define __LCD__

#include "LiquidCrystal_I2C.h"

class Lcd {
    private:
        LiquidCrystal_I2C* lcd;
        String lastDisplayedLines[2];
    public:
        Lcd(uint8_t address, uint8_t cols, uint8_t rows);
        void init();
        void updateLine(int line, const String& message);
        void clear();
};

#endif