// Include the library
#include <VirtualButton.h>

// Used to define how many switches the Arduino will handle
const byte SWITCH_COUNT = 3;

// Used to store if the virutal toggle switch is ON (true)
// NOTE: By default they are all false (OFF)
bool toggleSwitchON[SWITCH_COUNT];

// Set up the virtual button
VirtualButton vb(toggleSwitchON);

void setup() {
  // Set up the serial monitor
  Serial.begin(9600);

  // Loop through the initial array and display the values
  Serial.println("Initial array values:");
  for (int i = 0; i < SWITCH_COUNT; i++) {
    Serial.print(toggleSwitchON[i]);
    if (i != SWITCH_COUNT - 1)
      Serial.print(", ");
    else
      Serial.println();
  }

  // Toggle the first switch (the switch at index 0)
  vb.toggleSwitch(0);

  // Loop through the initial array and display the values after calling toggleSwitch() for the 1st switch
  Serial.println("Array after toggling switch 1:");
  for (int i = 0; i < SWITCH_COUNT; i++) {
    Serial.print(toggleSwitchON[i]);
    if (i != SWITCH_COUNT - 1)
      Serial.print(", ");
    else
      Serial.println();
  }

  // Loop through each switch and toggle it
  for (int i = 0; i < SWITCH_COUNT; i++) {
    vb.toggleSwitch(i);
  }

  // Loop through the initial array and display the values after  calling toggleSwitch() for all the switches
  Serial.println("Array after toggling all the switches:");
  for (int i = 0; i < SWITCH_COUNT; i++) {
    Serial.print(toggleSwitchON[i]);
    if (i != SWITCH_COUNT - 1)
      Serial.print(", ");
    else
      Serial.println();
  }
}

void loop() {
  // Do nothing
}