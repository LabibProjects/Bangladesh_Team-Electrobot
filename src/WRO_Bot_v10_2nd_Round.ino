
  #include "Wire.h"
  #include <MPU6050_light.h>
  #include <ESP32Servo.h>
  #include <NewPing.h>
  #include "HUSKYLENS.h"

  #define dbg 1
  #define turningAcceleration 8  //8
  #define distanceTolarance 8
  #define testClearance 44
  #define minClearance 50

  #define withThreshold 80
  #define narrowThreshold 35

  #define middlePos 70
  #define leftMax 30 //30 //20
  #define rightMax 110 //100 //120
  
  #define carSpeed 155
  #define turningDelay 500

  #define stopTime 2000
  #define endAngle 1030

  #define servoPin 15
  #define startSW 14

  #define rightSonarTrig 25  
  #define rightSonarEcho 26  
  #define leftSonarTrig 33
  #define leftSonarEcho 32
  #define maxDistance 200 

  #define mPin1 4
  #define mPin2 2
  #define enPin 17
  #define ledPin 13

  MPU6050 mpu(Wire);
  HUSKYLENS huskylens;

  Servo servo;  // create servo object to control a servo

  NewPing rightSonar(rightSonarTrig, rightSonarEcho, maxDistance);  // NewPing setup of pins and maximum distance.
  NewPing leftSonar(leftSonarTrig, leftSonarEcho, maxDistance);     // NewPing setup of pins and maximum distance.

  uint16_t leftSonarVal = 0, rightSonarVal = 0;
  uint16_t leftClearance = 0, rightClearance = 0, totalDistance = 0;
  int yawAngle = 0, rawYaw = 0;
  uint8_t startPosition = 1, lapsCount = 0;
  int pos = middlePos;
  bool gotMaxDistance = 0;
  int  tempLeftClearance = 0, tempRightClearance = 0;
  int currentTotalWidth = 0;
  bool narrowImportant = 0;
  bool blue =0, orange = 0, colorStts = 1;
  uint8_t color = 0;
  unsigned long currentTime = 0, prevTime = 0;
  unsigned long currentTime2 = 0, prevTime2 = 0;
  bool lapStts = 0;
  int clearanceTH = 0;

  void setup() {
    if(dbg) Serial.begin(115200);
    
    mpuInit();

    servo.attach(servoPin); 
    servo.write(middlePos);
    delay(200);

    pinMode(mPin1, OUTPUT); pinMode(mPin2, OUTPUT);
    pinMode(enPin, OUTPUT); pinMode(ledPin, OUTPUT);
    pinMode(startSW, INPUT_PULLUP); 
    digitalWrite(mPin1, 0); digitalWrite(mPin2, 0); digitalWrite(enPin, 0);

    calculateClearance();
    HuskyInit();
    
    while(digitalRead(startSW)){ 
      digitalWrite(ledPin, 1); delay(300);
      digitalWrite(ledPin, 0); delay(300);}
    forward(carSpeed);// while(9);
  }

  void loop() {
    leftSonarVal = leftSonar.ping_cm(); //delay(15);
    rightSonarVal = rightSonar.ping_cm();//delay(15);
    currentTotalWidth = leftSonarVal + rightSonarVal;

    color = getHusky();
    if(clearanceTH == 0 && color == 1) clearanceTH = 30; //red
    else if ( clearanceTH == 0 && color == 10 ) clearanceTH = -30; //green
    //else if() clearanceTH = 0;

    if( (clearanceTH > 0) && ( (leftSonarVal > 150) || (leftSonarVal < 10) ) ) { clearanceTH = 0;}
    else if( (clearanceTH < 0) && ( (rightSonarVal > 150) || (rightSonarVal < 10) ) ) { clearanceTH = 0; }

    if(leftSonarVal < 5 || leftSonarVal > 100) { leftSonarVal = maxDistance; }

    if(rightSonarVal < 5 || rightSonarVal > 100) { rightSonarVal = maxDistance; } 


         if ( startPosition == 0) { stayLeft2(tempLeftClearance + clearanceTH);  } 
    else if ( startPosition == 1) { stayRight2(tempRightClearance + clearanceTH);}

    lapsCheck2();
    
    if(dbg) debug();
    if(clearanceTH > 0){ digitalWrite(ledPin, 1);}
    if(clearanceTH <= 0){ digitalWrite(ledPin, 0);}
  }


  //////////////// Function //////////////////////

    
 void stayLeft2(uint16_t clearance){
    
     if ( (clearance + distanceTolarance)  < leftSonarVal ) { pos -= turningAcceleration; } // go left
    else if( clearance  < leftSonarVal ) { pos = middlePos - turningAcceleration; } // go left
    
    else if( (clearance - distanceTolarance) > leftSonarVal ) { pos += turningAcceleration; } // go right
    else if( clearance > leftSonarVal ) { pos = middlePos + turningAcceleration; } // go right
    else pos = middlePos;
         if( pos < leftMax) pos = leftMax;
    else if( pos > rightMax) pos = rightMax;
    servo.write(pos);
    

  }
  void stayRight2(uint16_t clearance){
    
    
     if ( (clearance + distanceTolarance)  < rightSonarVal ) { pos += turningAcceleration; } // go right
    else if( clearance  < rightSonarVal ) { pos = middlePos + turningAcceleration; } // go right
    
    else if( (clearance - distanceTolarance) > rightSonarVal ) { pos -= turningAcceleration; } // go left
    else if( clearance > rightSonarVal ) { pos = middlePos - turningAcceleration; } // go left
    else pos = middlePos;
         if( pos < leftMax) pos = leftMax;
    else if( pos > rightMax) pos = rightMax;
    servo.write(pos);
    
  }

void calculateClearance(){
  digitalWrite(ledPin, 1);
  leftClearance = 0; rightClearance = 0;
  for (int i =0; i< 10; i++){
    leftClearance += leftSonar.ping_cm(); //delay(25);
    rightClearance += rightSonar.ping_cm(); //delay(25);
    
  }
  leftClearance /= 10;
  rightClearance /= 10;
  if( leftClearance > rightClearance){
    startPosition = 1; // 1 is for right
  }
  else {
      startPosition = 0; // 1 is for left
  }

  // digitalWrite(ledPin, startPnarrowImportantosition);
  if( leftClearance < minClearance ) leftClearance = minClearance;
  if( rightClearance < minClearance ) rightClearance = minClearance;
  
  tempLeftClearance = leftClearance;
  tempRightClearance = rightClearance; 

}


uint8_t getHusky() {
  blue = 0; orange = 0;
  huskylens.request(1); blue = huskylens.count(1);
  huskylens.request(2); orange = huskylens.count(2);
  // Serial.print(blue); Serial.print(" ");
  // Serial.print(orange); Serial.println(" ");

  return (blue + orange*10);
}

void HuskyInit(){
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
}
void HuskyLens_Test() {
  if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  else if (!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
  else if (!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
  else Serial.println(F("HuskyLens OK!!!"));
}

void debug(){
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
    Serial.print("  clr: "); Serial.print(color);

    Serial.println("");
}

void lapsCheck2() {
  mpu.update();
  rawYaw = abs(mpu.getAngleZ())  ;
  //Serial.print(yawAngle);
  //rawYaw = yawAngle;

  currentTime = millis();
  
  if( rawYaw > endAngle ){  // 1030
    if(colorStts) { colorStts = 0; prevTime2 = currentTime;}
  
    if( (currentTime - prevTime2) > stopTime ){
      stop(); while(9);   
  }
  }
}

void forward(byte speed) {
    // analogWrite(enPin, speed);
    digitalWrite(enPin, 1); 
    // digitalWrite(mPin1, 0); digitalWrite(mPin2, 1);
    digitalWrite(mPin1, 0); analogWrite(mPin2, speed);
    //Serial.println("forward");

}

void stop() {
  // analogWrite(enPin, speed);
  digitalWrite(enPin, 0); 
  // digitalWrite(mPin1, 0); digitalWrite(mPin2, 1);
  digitalWrite(mPin1, 0); analogWrite(mPin2, 0); delay(500);
}


void mpuInit() {
  Wire.begin();

  byte status = mpu.begin();
  // Serial.print(F("MPU6050 status: "));
  // Serial.println(status);
  while (status != 0) {}  // stop everything if could not connect to MPU6050

  // Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets();  // gyro and accelero
  // Serial.println("Done!\n");
}