// // #include <Wire.h>
// // #include <MPU6050_light.h>

// // MPU6050 mpu1(Wire);
// // MPU6050 mpu2(Wire);

// // void setup() {
// //   Serial.begin(115200);
// //   Wire.begin();

// //   // Initialize first MPU6050
// //   mpu1.begin(0x68);
// //   Serial.println("MPU6050 #1 initialized");

// //   // Initialize second MPU6050
// //   mpu2.begin(0x69);
// //   Serial.println("MPU6050 #2 initialized");
// // }

// // void loop() {
// //   mpu1.update();
// //   mpu2.update();

// //   Serial.print("MPU1 Accel X: ");
// //   Serial.println(mpu1.getAccX());

// //   Serial.print("MPU2 Accel X: ");
// //   Serial.println(mpu2.getAccX());

// //   delay(500);
// // }
// #include <Wire.h>
// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>

// Adafruit_MPU6050 mpu1;
// Adafruit_MPU6050 mpu2;

// void setup() {
//   Serial.begin(115200);
//   Wire.begin();

//   // Initialize first MPU6050
//   if (!mpu1.begin(0x68)) {
//     Serial.println("Failed to find MPU6050 #1");
//     while (1);
//   }

//   // Initialize second MPU6050
//   if (!mpu2.begin(0x69)) {
//     Serial.println("Failed to find MPU6050 #2");
//     while (1);
//   }
// }

// void loop() {
//   sensors_event_t a1, g1, temp1;
//   sensors_event_t a2, g2, temp2;

//   // Read from first MPU6050
//   mpu1.getEvent(&a1, &g1, &temp1);
//   Serial.print("MPU1 Accel X: ");
//   Serial.println(a1.acceleration.x);

//   // Read from second MPU6050
//   mpu2.getEvent(&a2, &g2, &temp2);
//   Serial.print("MPU2 Accel X: ");
//   Serial.println(a2.acceleration.x);

//   delay(500);
// }
#include "Wire.h"
#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"

Adafruit_MPU6050 mpu1;
Adafruit_MPU6050 mpu2;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize first MPU6050
  if (!mpu1.begin(0x68)) {
    Serial.println("Failed to find MPU6050 #1");
    while (1);
  }

  // Initialize second MPU6050
  if (!mpu2.begin(0x69)) {
    Serial.println("Failed to find MPU6050 #2");
    while (1);
  }
}

void loop() {
  sensors_event_t a1, g1, temp1;
  sensors_event_t a2, g2, temp2;

  // Read from first MPU6050
  mpu1.getEvent(&a1, &g1, &temp1);
  Serial.print("MPU1 Accel X: ");
  Serial.println(a1.acceleration.x);

  // Read from second MPU6050
  mpu2.getEvent(&a2, &g2, &temp2);
  Serial.print("MPU2 Accel X: ");
  Serial.println(a2.acceleration.x);

  delay(500);
}
