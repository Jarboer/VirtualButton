/*
  VirtualButton.cpp - Library for reading from a virtual button aka the keyboard
  Created by Jarrett on July 21, 2022
*/
#include "Arduino.h"
#include "VirtualButton.h"

/* This is a constructor for VirtualButton which takes a for toggleSwitchesON array.*/
VirtualButton::VirtualButton(bool toggleSwitchesON[]) {
  _userButtonVal = 0;
  _helperRanOnce = false;
  _toggleSwitchesON = toggleSwitchesON;
}

/* This is a constructor for VirtualButton which takes no arguments.
   NOTE: Use this when you only need access to digitalRead()*/
VirtualButton::VirtualButton() {
  _userButtonVal = 0;
  _helperRanOnce = false;
  _toggleSwitchesON = {};
}

// This method switches the toggleSwitchesON value and returns it
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
  /* If _helperRanOnce is false then display an error message to inform the
     user that they must run virtualDigitalReadHelper() first to monitor thier input*/
  if (_helperRanOnce == false) {
    Serial.println(F("ERROR: Call virtualDigitalReadHelper() first to monitor inputs. Stopping..."));
    while (true) {
      // Do nothing
    }
  }

  // Check if the user entered a value and if it is a configured button
  if (_userButtonVal != 0 && buttonPin == _userButtonVal) {
    // Reset the _userButtonVal to prevent recursion
    _userButtonVal = 0;
    // It is a button so return HIGH
    return HIGH;
  }

  return LOW;  // It isn't so return LOW
}

/* This method is used to monitor the input from the user in the
   Serial Monitor for the virtualDigitalRead() method*/
void VirtualButton::virtualDigitalReadHelper() {
  // The method was called once
  _helperRanOnce = true;

  // Set the userButtonVal to what the user typed
  _userButtonVal = serialReadByte();
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
  if (serialInt == 0 || serialInt < -1 || serialInt > 255) {
    // Display the error
    Serial.println(F("Invalid value entered (the input must be an int, > 0 and <= 255). Try again."));
  } else if (serialInt != -1) {  // Otherwise, the value is valid
    // Convert the int to a byte and return it
    return byte(serialInt);
  }

  // Return 0 as there was an error
  return 0;
}