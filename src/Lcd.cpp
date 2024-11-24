#include "Lcd.h"

Lcd::Lcd(uint8_t address, uint8_t cols, uint8_t rows) {
    lcd = new LiquidCrystal_I2C(address, cols, rows);
    lastDisplayedLines[0] = "";
    lastDisplayedLines[1] = "";
}

void Lcd::init() {
    lcd->init();
    lcd->backlight();
    lcd->clear();
}

void Lcd::updateLine(int line, const String& message) {
    if (lastDisplayedLines[line] != message) {
        lcd->setCursor(0, line);
        lcd->print("                ");
        lcd->setCursor(0, line);
        lcd->print(message);
        lastDisplayedLines[line] = message;
    }
}

void Lcd::clear() {
    lcd->clear();
    lastDisplayedLines[0] = 1;
    lastDisplayedLines[1] = 2;
}