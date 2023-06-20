/**
 * VirtualButton.h - Library for reading from a virtual button aka the keyboard
 * Created by Jarrett on July 21, 2022
 */
#ifndef VirtualButton_h
#define VirtualButton_h

#include "Arduino.h"

class VirtualButton {
 public:
  /**
   * This is a constructor for VirtualButton which takes a for toggleSwitchesON array.
   *
   * @param toggleSwitchesON The reference to the array storing toggleSwitches that are ON
   */
  VirtualButton(bool toggleSwitchesON[]);

  /**
   * This is a constructor for VirtualButton which takes no arguments.
   * NOTE: Use this when you only need access to digitalRead()
   */
  VirtualButton();

  /**
   * This method switches the toggleSwitchesON value and returns it
   *
   * @param switchNum The value of the assigned switch in the array
   * @return Returns the new value of the switch in the array
   */
  bool toggleSwitch(int switchNum);

  /**
   * This method is used to simulate digitalRead() by reading the input byte
   * from the user and checks if the value is a configured button.
   *
   * @return Returns HIGH if the above is true, otherwise, it returns LOW.
   */
  int virtualDigitalRead(byte buttonPin);

  /**
   * This method is used to monitor the input from the user in the
   * Serial Monitor for the virtualDigitalRead() method.
   */
  void virtualDigitalReadHelper();

  /**
   * This method is used to read and process the incoming byte from the Serial Monitor. It does this by building
   * a char array which is determined by a new line (Ex: 123 then enter). It then tries to convert the
   * value to a byte. It only accepts values from 1 to 255, otherwise it will display an error and
   * setfinalByte to 0.
   */
  void serialReadByte();

  /**
   *  This is a helper function to convert a char array to a byte
   */
  void convertToByte(const char fullInput[], const unsigned int inputPosition);

 private:
  byte _userButtonVal;
  bool _helperRanOnce;
  bool *_toggleSwitchesON;
};

#endif