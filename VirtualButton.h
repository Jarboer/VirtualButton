/*
  VirtualButton.h - Library for reading from a virtual button aka the keyboard
  Created by Jarrett on July 21, 2022
*/
#ifndef VirtualButton_h
#define VirtualButton_h

#include "Arduino.h"

class VirtualButton {
  public:
    /* This is a constructor for VirtualButton which takes a for toggleSwitchesON array.*/
    VirtualButton(bool toggleSwitchesON[]);
    /* This is a constructor for VirtualButton which takes no arguments.
    NOTE: Use this when you only need access to digitalRead()*/
    VirtualButton();
    bool toggleSwitch(int switchNum);
    void virtualDigitalReadHelper();
    int virtualDigitalRead(byte buttonPin);
    byte serialReadByte();

  private:
    byte _userButtonVal;
    bool _helperRanOnce;
    bool *_toggleSwitchesON;
};

#endif