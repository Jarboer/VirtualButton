#include <VirtualButton.h>

// Used to define how many switches the Arduino will handle
const byte SWITCH_COUNT = 3;

/* Used to set the input pins for the sensor pins being read. 
   These are the values that you will enter to toggle a switch*/
const char sensorPins[SWITCH_COUNT] = { 2, 3, 4 };

// Used to store the button's state
byte buttonState = LOW;

// Set up the VirtualButton class
VirtualButton vb;

void setup() {
  // Set up the serial monitor
  Serial.begin(9600);
}

void loop() {
  // Call the method to monitor the Serial Monitor for inputs
  // NOTE: This must be called before virtualDigitalRead()
  vb.virtualDigitalReadHelper();

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