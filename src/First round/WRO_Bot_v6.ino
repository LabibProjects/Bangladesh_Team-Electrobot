  #include "Wire.h"
  #include <MPU6050_light.h>
  #include <ESP32Servo.h>
  #include <NewPing.h>

  #define dbg 1
  #define turningAcceleration 8  //8
  #define distanceTolarance 8
  #define testClearance 44
  #define minClearance 20
  #define withThreshold 80
  #define narrowThreshold 35
  #define middlePos 59
  #define leftMax 20 //30 //20
  #define rightMax 120 //100 //120
  #define carSpeed 200

  #define servoPin 15

  #define rightSonarTrig 25  
  #define rightSonarEcho 26  
  #define leftSonarTrig 33
  #define leftSonarEcho 32
  #define maxDistance 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

  #define mPin1 4
  #define mPin2 2
  #define enPin 17
  #define ledPin 13

  MPU6050 mpu(Wire);

  Servo servo;  // create servo object to control a servo

  NewPing rightSonar(rightSonarTrig, rightSonarEcho, maxDistance);  // NewPing setup of pins and maximum distance.
  NewPing leftSonar(leftSonarTrig, leftSonarEcho, maxDistance);     // NewPing setup of pins and maximum distance.

  uint16_t leftSonarVal = 0, rightSonarVal = 0;
  uint16_t leftClearance = 0, rightClearance = 0, totalDistance = 0;
  int yawAngle = 0;
  uint8_t startPosition = 1, lapsCount = 0;
  int pos = middlePos;
  bool gotMaxDistance = 0;
  int  tempLeftClearance = 0, tempRightClearance = 0;
  bool narrowImportant = 0;
  void setup() {
    if(dbg) Serial.begin(115200);
   // core2Init();
    mpuInit();
    servo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
    servo.write(middlePos);
    delay(200);

    pinMode(mPin1, OUTPUT); pinMode(mPin2, OUTPUT);
    pinMode(enPin, OUTPUT); pinMode(ledPin, OUTPUT);
    digitalWrite(mPin1, 0); digitalWrite(mPin2, 0); digitalWrite(enPin, 0);

    calculateClearance();

    delay(1000);
    //calculateClearance();
   //while(9) {calculateClearance();}
  // while(9) {forward(180); delay(10);}
    // rightClearance = testClearance;
    // leftClearance = testClearance;
    //lapsRun(200);
    forward(carSpeed);
  }

  void loop() {
    leftSonarVal = leftSonar.ping_cm(); //delay(15);
    rightSonarVal = rightSonar.ping_cm();//delay(15);
    int currentTotalWidth = leftSonarVal + rightSonarVal;

    if(leftSonarVal < 5 || leftSonarVal > 85) { 
      leftSonarVal = maxDistance; 
      if(gotMaxDistance == 0 ) {
         gotMaxDistance =1; startPosition = 0; 
         if(leftClearance > narrowThreshold) narrowImportant = 1;
        } 
      }
    if(rightSonarVal < 5 || rightSonarVal > 85) {
       rightSonarVal = maxDistance; 
       if(gotMaxDistance == 0 ) {
         gotMaxDistance =1; startPosition = 1; 
         if(rightClearance > narrowThreshold) narrowImportant = 1;
        }
      }

    lapsCheck(3);

    if(dbg){
    Serial.print(leftSonarVal); Serial.print("  cm    R:  ");
    Serial.print(rightSonarVal); Serial.print("  cm  ");
    // Serial.print("  yaw main : "); Serial.print(yawAngle);
    // Serial.print("  Laps: "); Serial.print(lapsCount);
    Serial.print("  lCL: "); Serial.print(leftClearance);
    Serial.print("  rcl: "); Serial.print(rightClearance);
    Serial.print("  NI: "); Serial.print(narrowImportant);
    Serial.print("  TW: "); Serial.print(currentTotalWidth);
    Serial.print("  stPos: "); Serial.print(startPosition);
    Serial.print("  Pos: "); Serial.print(pos);

      Serial.println("");
    }

    if(narrowImportant){
      if (currentTotalWidth < withThreshold){
        tempLeftClearance = minClearance;
        tempRightClearance = minClearance; 
      }
      else if ( (currentTotalWidth > withThreshold) && (currentTotalWidth < 110) ) {
        tempRightClearance = rightClearance;
        tempLeftClearance = leftClearance;
      }
    }

         if ( startPosition == 0) { stayLeft2(tempLeftClearance);  } 
    else if ( startPosition == 1) { stayRight2(tempRightClearance);}
    digitalWrite(ledPin, narrowImportant);
  }

//void Task1code();  // 2nd loop
