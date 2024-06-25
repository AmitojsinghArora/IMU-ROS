#include <Arduino.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include <Kalman.h>

// Set the FreeSixIMU object
FreeSixIMU sixDOF = FreeSixIMU();

// Set up the Kalman filter for angle estimation
Kalman kalmanX;
Kalman kalmanY;

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float angleX, angleY;
float kalAngleX, kalAngleY;

unsigned long timer;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  delay(5);
  sixDOF.init(); // Begin the IMU
  delay(5);

  timer = micros();

  // Initialize Kalman filters
  kalmanX.setQangle(0.001);
  kalmanX.setQbias(0.003);
  kalmanX.setRmeasure(0.03);
  kalmanX.setAngle(0);

  kalmanY.setQangle(0.001);
  kalmanY.setQbias(0.003);
  kalmanY.setRmeasure(0.03);
  kalmanY.setAngle(0);
}

void loop() {
  float values[6]; // Array to hold accelerometer and gyroscope values

  sixDOF.getValues(values);

  accX = values[0];
  accY = values[1];
  accZ = values[2];
  gyroX = values[3];
  gyroY = values[4];
  gyroZ = values[5];

  // Calculate delta time
  unsigned long now = micros();
  float dt = (now - timer) / 1000000.0;
  timer = now;

  // Calculate angle using accelerometer
  angleX = atan2(accY, accZ) * RAD_TO_DEG;
  angleY = atan2(-accX, accZ) * RAD_TO_DEG;

  // Apply Kalman filter to estimate angle
  kalAngleX = kalmanX.getAngle(angleX, gyroX, dt);
  kalAngleY = kalmanY.getAngle(angleY, gyroY, dt);

  // Print acceleration values
  Serial.print("Accel X: ");
  Serial.print(accX);
  Serial.print(" | Accel Y: ");
  Serial.print(accY);
  Serial.print(" | Accel Z: ");
  Serial.println(accZ);

  // Print angle values
  Serial.print("Angle X: ");
  Serial.print(kalAngleX);
  Serial.print(" | Angle Y: ");
  Serial.println(kalAngleY);

  delay(600);
}