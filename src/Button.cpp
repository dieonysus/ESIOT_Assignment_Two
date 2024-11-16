#include "Button.h"
#include <Arduino.h>

Button::Button(int pin,unsigned long debounceTime = 40){
  this->pin = pin;
  buttonState = LOW;
  lastButtonState = LOW;
  lastPressTime = 0;
  this->debounceTime = debounceTime ;
  pinMode(pin, INPUT);
}

bool Button::isPressed(){
  int reading = digitalRead(pin);

  if (reading != lastButtonState) {
        lastPressTime = millis();
      }

  if ((millis() - lastPressTime) > debounceTime) {
        if (reading != buttonState) {
          buttonState = reading;
          if (buttonState == HIGH) {
            return true;
          }
        }
        lastButtonState = reading;
        return false;
      }

  
}