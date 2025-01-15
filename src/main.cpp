// // // #include <Wire.h>
// // // #include <MPU6050_light.h>

// // // MPU6050 mpu1(Wire);
// // // MPU6050 mpu2(Wire);

// // // void setup() {
// // //   Serial.begin(115200);
// // //   Wire.begin();

// // //   // Initialize first MPU6050
// // //   mpu1.begin(0x68);
// // //   Serial.println("MPU6050 #1 initialized");

// // //   // Initialize second MPU6050
// // //   mpu2.begin(0x69);
// // //   Serial.println("MPU6050 #2 initialized");
// // // }

// // // void loop() {
// // //   mpu1.update();
// // //   mpu2.update();

// // //   Serial.print("MPU1 Accel X: ");
// // //   Serial.println(mpu1.getAccX());

// // //   Serial.print("MPU2 Accel X: ");
// // //   Serial.println(mpu2.getAccX());

// // //   delay(500);
// // // }
// // #include <Wire.h>
// // #include <Adafruit_MPU6050.h>
// // #include <Adafruit_Sensor.h>

// // Adafruit_MPU6050 mpu1;
// // Adafruit_MPU6050 mpu2;

// // void setup() {
// //   Serial.begin(115200);
// //   Wire.begin();

// //   // Initialize first MPU6050
// //   if (!mpu1.begin(0x68)) {
// //     Serial.println("Failed to find MPU6050 #1");
// //     while (1);
// //   }

// //   // Initialize second MPU6050
// //   if (!mpu2.begin(0x69)) {
// //     Serial.println("Failed to find MPU6050 #2");
// //     while (1);
// //   }
// // }

// // void loop() {
// //   sensors_event_t a1, g1, temp1;
// //   sensors_event_t a2, g2, temp2;

// //   // Read from first MPU6050
// //   mpu1.getEvent(&a1, &g1, &temp1);
// //   Serial.print("MPU1 Accel X: ");
// //   Serial.println(a1.acceleration.x);

// //   // Read from second MPU6050
// //   mpu2.getEvent(&a2, &g2, &temp2);
// //   Serial.print("MPU2 Accel X: ");
// //   Serial.println(a2.acceleration.x);

// //   delay(500);
// // }
// #include "Wire.h"
// #include "Adafruit_MPU6050.h"
// #include "Adafruit_Sensor.h"

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
// #include "Wire.h"
// #include "Adafruit_MPU6050.h"
// #include "Adafruit_Sensor.h"

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
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/kernels/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#include "model_data.h" // Include the TensorFlow Lite model header file

Adafruit_MPU6050 mpu1;
Adafruit_MPU6050 mpu2;

// TensorFlow Lite model setup
constexpr int kTensorArenaSize = 2 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
tflite::MicroErrorReporter error_reporter;
tflite::AllOpsResolver resolver;
tflite::MicroInterpreter* interpreter;
TfLiteTensor* input;
TfLiteTensor* output;

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

  // Load TensorFlow Lite model
  const tflite::Model* model = tflite::GetModel(model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema version mismatch!");
    while (1);
  }

  // Initialize interpreter
  interpreter = new tflite::MicroInterpreter(model, resolver, tensor_arena, kTensorArenaSize, &error_reporter);
  if (interpreter->AllocateTensors() != kTfLiteOk) {
    Serial.println("AllocateTensors() failed");
    while (1);
  }

  input = interpreter->input(0);
  output = interpreter->output(0);
}

void loop() {
  sensors_event_t a1, g1, temp1;
  sensors_event_t a2, g2, temp2;

  // Read from first MPU6050
  mpu1.getEvent(&a1, &g1, &temp1);
  
  // Read from second MPU6050
  mpu2.getEvent(&a2, &g2, &temp2);

  // Populate input tensor
  input->data.f[0] = a1.acceleration.x;
  input->data.f[1] = a1.acceleration.y;
  input->data.f[2] = a1.acceleration.z;
  input->data.f[3] = a2.acceleration.x;
  input->data.f[4] = a2.acceleration.y;
  input->data.f[5] = a2.acceleration.z;

  // Run inference
  if (interpreter->Invoke() != kTfLiteOk) {
    Serial.println("Invoke failed");
    return;
  }

  // Get and print the output class
  int predicted_class = -1;
  float max_score = -1;
  for (int i = 0; i < 6; i++) {  // Assuming 6 output classes
    float score = output->data.f[i];
    if (score > max_score) {
      max_score = score;
      predicted_class = i;
    }
  }

  Serial.print("Predicted class: ");
  Serial.println(predicted_class);

  delay(500); // Adjust delay as needed
}