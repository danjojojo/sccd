#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "../constants/enums.h"

class Button
{

private:
    unsigned int leftButtonPin;
    unsigned int rightButtonPin;

public:
    Button(unsigned int leftBtnPn, unsigned int rightBtnPn);
    void init();
    bool holdButtonForSeconds(unsigned int btnPin, int milliseconds);
    ButtonType getButtonPressed();
};

#endif
