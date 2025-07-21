#include "../include/class/button.h"

Button::Button(unsigned int leftBtnPn, unsigned int rightBtnPn)
{
    this->leftButtonPin = leftBtnPn;
    this->rightButtonPin = rightBtnPn;
    init();
}

void Button::init()
{
    pinMode(leftButtonPin, INPUT_PULLUP);
    pinMode(rightButtonPin, INPUT_PULLUP);
}

bool Button::holdButtonForSeconds(unsigned int btnPin, int holdDuration)
{
    static unsigned long pressedTime = 0;
    static bool isHolding = false;

    int state = digitalRead(btnPin);

    if (state == LOW)
    {
        if (!(isHolding))
        {
            pressedTime = millis();
            isHolding = true;
        }
        unsigned long heldTime = millis() - pressedTime;
        Serial.println(heldTime);
        if (heldTime >= holdDuration - 800)
        {
            return true;
        }
    }
    else
    {
        isHolding = false;
        pressedTime = 0;
    }

    return false;
}

ButtonType Button::getButtonPressed()
{
    if (holdButtonForSeconds(leftButtonPin, 2000))
        return LEFT_HOLD_2_SECONDS;
    if (digitalRead(leftButtonPin) == LOW)
        return LEFT_ONCE;
    if (digitalRead(rightButtonPin) == LOW)
        return RIGHT_ONCE;
    return NONE;
}