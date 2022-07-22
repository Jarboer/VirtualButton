#include <VirtualButton.h>

// Used to define how many switches the Arduino will handle
const byte SWITCH_COUNT = 3;

// Used to set the input pins for the sensor pins being read
// Set to the value of the pin on the Arduino
const char sensorPins[SWITCH_COUNT] = { 2, 3, 4 };

// Used to store the value entered by the user for the virtual button
byte inputByte = 0;

// Used to store the button's state
byte buttonState = LOW;

// Used to store if the virutal toggle switch is ON (true)
// NOTE: By default they are all false (OFF)
bool toggleSwitchON[SWITCH_COUNT];

// Set up the virtual button
// NOTE: You must include the & before the inputByte varible when using this method
VirtualButton vb(&inputByte, toggleSwitchON);

void setup() {
  // Set up the serial monitor
  Serial.begin(9600);
}

void loop() {
  // Set the value entered by the user for the virtual button
  inputByte = vb.serialReadByte();

  // Show the value entered
  if (inputByte != 0) {
    Serial.println(inputByte);
  }

  // Loop for the number of switches to read thier coresponding pins
  for (int machineIndex = 0; machineIndex < SWITCH_COUNT; machineIndex++) {
    // Set the button's state
    buttonState = vb.virtualDigitalRead(sensorPins[machineIndex]);

    // If the button is pressed
    if (buttonState == HIGH) {
      Serial.println("Button pressed!");
    }
  }
}