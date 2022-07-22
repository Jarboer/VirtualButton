/*
  VirtualButton.h - Library for reading from a virtual button aka the keyboard
  Created by Jarrett on July 21, 2022
*/
#ifndef VirtualButton_h
#define VirtualButton_h

#include "Arduino.h"

class VirtualButton {
    public:
        VirtualButton(byte *userButtonVal, bool toggleSwitchesON[]);
        VirtualButton(bool toggleSwitchesON[]);
        bool toggleSwitch(int switchNum);
        int virtualDigitalRead(byte buttonPin);
        byte serialReadByte();
    private:
     byte *_userButtonVal; // NOTE: When you refer to _userButtonVal in the VirtualButton.cpp class you must use *_userButtonVal to get the value
     bool *_toggleSwitchesON;
};

#endif