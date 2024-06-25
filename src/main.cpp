
#include <Arduino.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>

// Set the FreeSixIMU object
FreeSixIMU sixDOF = FreeSixIMU();


void setup() {
  Serial.begin(9600);
  Wire.begin();

  delay(5);
  sixDOF.init(); // Begin the IMU
  delay(5);
}

void loop() {
  float values[6]; // Array to hold accelerometer and gyroscope values

  sixDOF.getValues(values);
  

  // Print accelerometer values
  Serial.print("Accel X: ");
  Serial.print(values[0]);
  Serial.print(" | Accel Y: ");
  Serial.print(values[1]);
  Serial.print(" | Accel Z: ");
  Serial.println(values[2]);

  delay(600);

  

}
