/**
 * VirtualButton.cpp - Library for reading from a virtual button aka the keyboard
 * Created by Jarrett on July 21, 2022
 */
#include "VirtualButton.h"

VirtualButton::VirtualButton(bool toggleSwitchesON[]) {
  _userButtonVal = 0;
  _helperRanOnce = false;
  _toggleSwitchesON = toggleSwitchesON;
}

VirtualButton::VirtualButton() {
  _userButtonVal = 0;
  _helperRanOnce = false;
  _toggleSwitchesON = {};
}

bool VirtualButton::toggleSwitch(int switchNum) {
  _toggleSwitchesON[switchNum] = !_toggleSwitchesON[switchNum];  // The ! switches the bool value
  return _toggleSwitchesON[switchNum];
}

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
    // Reset the _userButtonVal to prevent getting stuck running virtualDigitalRead
    _userButtonVal = 0;
    // It is a button so return HIGH
    return HIGH;
  }

  return LOW;  // It isn't so return LOW
}

void VirtualButton::virtualDigitalReadHelper() {
  // The method was called once
  _helperRanOnce = true;

  // Call serialReadByte read to what the user typed
  // It also sets the _userButtonVal
  serialReadByte();
}

void VirtualButton::serialReadByte() {
  /* NOTE: Local static variables allow the data to update without being reset
           while prevent them from being called outside this function.

           Also, variables cannot be declared within a case statement*/
  // Set how much serial data we expect before a newline
  const unsigned int MAX_INPUT = 50;
  // Used to store the full input from the user (constructed byte by byte)
  static char fullInput[MAX_INPUT];
  // Used to store the position of the current byte
  static unsigned int inputPosition = 0;

  byte inputByte;

  // While the serial data is available, process it
  while (Serial.available() > 0) {
    inputByte = Serial.read();

    switch (inputByte) {
      case '\r':                          // Carriage return
      case '\n':                          // End of new line
        fullInput[inputPosition] = '\0';  // Add terminating null byte

        // Call this method to convert fullInput to a byte
        convertToByte(fullInput, inputPosition);

        // Reset buffer's inputPosition for next time
        inputPosition = 0;
        break;

      default:
        // Keep adding to the fullInput if it isn't full (MAX_INPUT - 1 to allow for terminating null byte)
        if (inputPosition < (MAX_INPUT - 1)) {
          // Add the inputByte to the array (converts from byte to char automatically)
          fullInput[inputPosition] = inputByte;
          inputPosition++;  // Increase the inputPosition
        }
        break;
    }
  }
}

void VirtualButton::convertToByte(const char fullInput[], const unsigned int inputPosition) {
  // Used to store if the fullInput is a positive integer
  bool positiveInt = true;
  // Used to store the integer entered by the user (fullInput converted)
  int serialInt = 0;

  // Loop through all the characters
  for (int i = 0; i < inputPosition; i++) {
    // If the character isn't a digit set postInt to false
    if (!isDigit(fullInput[i])) {
      positiveInt = false;
      break;  // Leave loop early
    }
  }

  // Convert the fullInput to an int and store it
  serialInt = atoi(fullInput);

  // Check if the value is invalid
  if (positiveInt == false || serialInt <= 0 || serialInt > 255) {
    // Display the error
    Serial.println(F("Invalid value entered (the input must be an int, > 0 and <= 255). Try again."));
  } else {  // Otherwise, the value is valid
    // Convert the int to a byte and store it
    _userButtonVal = byte(serialInt);
  }
}