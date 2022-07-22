/*
  VirtualButton.cpp - Library for reading from a virtual button aka the keyboard
  Created by Jarrett on July 21, 2022
*/
#include "Arduino.h"
#include "VirtualButton.h"

/* This is a constructor for VirtualButton which takes a reference to userButtonVal and the toggleSwitchesON array.
   _userButtonVal will refer to the reference stored userButtonVal and so when ever you change that variable in the sketch
   _userButtonVal will also be able to reference the same value. */
/*  NOTE: To pass the refence, when intializing VirtualButton, the variable passed to userButtonVal must have & before 
   the variable name like this: &myVariable*/
VirtualButton::VirtualButton(byte *userButtonVal, bool toggleSwitchesON[]) {
  _userButtonVal = userButtonVal;
  _toggleSwitchesON = toggleSwitchesON;
}

/* This is a constructor for VirtualButton which takes a for toggleSwitchesON array.*/
/* NOTE: Use this when you don't need to use virtualDigitalRead.*/
VirtualButton::VirtualButton(bool toggleSwitchesON[]) {
  _userButtonVal = 0;
  _toggleSwitchesON = toggleSwitchesON;
}

// This method switches the toggleSwitchesON value and return it
bool VirtualButton::toggleSwitch(int switchNum) {
  if (_toggleSwitchesON[switchNum] == true) {
    _toggleSwitchesON[switchNum] = false;
  } else {
    _toggleSwitchesON[switchNum] = true;
  }
  return _toggleSwitchesON[switchNum];
}

/*  This method is used to simulate digitalRead() by reading the input byte 
    from the user and check if the value is a configured button. If it is
    it returns HIGH, otherwise, it returns LOW.*/
int VirtualButton::virtualDigitalRead(byte buttonPin) {

  // Check if the user entered a value and if it is a configured button
  if (*_userButtonVal != 0 && buttonPin == *_userButtonVal) {
    // Reset the userButtonVal to prevent recursion
    *_userButtonVal = 0;
    // It is a button so return HIGH
    return HIGH;
  }

  return LOW;  // It isn't so return LOW
}

/*  This method is used to read from the serial monitor and try to convert the value 
    to a byte. It only accepts values from 1 to 255, otherwise it will display an 
    error and return 0.*/
byte VirtualButton::serialReadByte() {
  // Used to store the serial monitor value as an int
  int serialInt = -1;

  // Check if there is characters available
  if (Serial.available() > 0) {
    // Store the parsed integer
    serialInt = Serial.parseInt();
  }

  // If serialInt isn't the default value
  // This is to make -1 result in an error (a timeout error)
  if (serialInt != -1) {
    Serial.read();  // Read the new line char from the buffer
  }

  // Check if the value is valid
  if (serialInt == 0 || serialInt < -1) {
    // Display the error
    Serial.println(F("An invalid character was entered (the input must be an int and > 0). Try again."));
  } else if (serialInt > 255) {  // Check if the value is too large
    // Display the error
    Serial.println(F("The value entered was too large (must be <= 255). Try again."));
  } else if (serialInt != -1) {  // Otherwise, the value is valid
    // Convert the int to a byte and return it
    return byte(serialInt);
  }

  // Return 0 as there was an error
  return 0;
}