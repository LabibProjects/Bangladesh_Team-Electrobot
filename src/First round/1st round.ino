#include <NewPing.h>
#include <PIDController.h>
#include <ESP32Servo.h>
#include <MPU6050_light.h>
#include <BTS7960.h>
#include <HUSKYLENS.h>

#define endAngle 1080  //3 laps
#define MPU_INT 5
#define MPU_AD0 23
#define SERVO_PIN 15
#define BTS_REN 17
#define BTS_LEN 17
#define BTS_LPWM 4
#define BTS_RPWM 2

#define MAX_DISTANCE 200 
#define ULTRA_RPIN 26
#define ULTRA_LPIN 25

#define clockwise 1
#define anticlockwise 0

///////////////////////////////////////////////////////////////////////

int yawAngle = 0, startAngle = 0;

unsigned long DisTimer = 0, MPUtimer = 0, lapTimer = 0;

int mainSpeed = 120;
bool start = false;
long LD, RD;
char dir;
int ID1 = 1;
//void Get_yawAngle();
///////////////////////////////////////////////////////////////////////
MPU6050 mpu(Wire);
Servo myservo;
HUSKYLENS huskylens;
NewPing sonarR(ULTRA_RPIN, ULTRA_RPIN, MAX_DISTANCE), sonarL( ULTRA_LPIN,  ULTRA_LPIN, MAX_DISTANCE);    
BTS7960 motor1(BTS_LEN, BTS_REN, BTS_LPWM, BTS_RPWM);   //This method will create a object of the class BTS7960

void setup () {
  Serial.begin(115200);  // Some methods require the Serial.begin() method to be called first'

  Wire.begin();
  while (mpu.begin() != 0) {
    Serial.print(F("MPU6050 failed to initialize!"));
  }
  mpu.calcOffsets(); // gyro and accelero
  lapTimer = millis();
  while (!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }

  myservo.attach(SERVO_PIN);
  myservo.write(90); // 50, 90, 140
  motor1.begin();                           //This method will set the motor driver pins as output
  motor1.enable();                          //This method will set the L_EN and R_EN to HIGH or digitalWrite them to +5v/3v depending on your mcu

  motor1.pwm = 70;
  motor1.front();
  Rotate(20, clockwise);
  Get_yawAngle();
  start = true;
}

int endAngleReached = 0;

void loop () {
  Get_Distance();
  Get_yawAngle();
  HuskyLens_Test();
  if (yawAngle > endAngle - 18 && yawAngle < endAngle + 18) {
    endAngleReached++;
    Serial.println(String() + F("Lap: ") + endAngleReached );
    if( endAngleReached == 3 ) {
        motor1.stop();
        Rotate(0, anticlockwise);
        Serial.println( F("Goal Line") );
    }
  }


}
///////////////////////   Rotate    ////////////////////
void Rotate(int angle, int dir ) {
  if( dir == clockwise ) angle += 90;
  else angle = 90 - angle;
  myservo.writeMicroseconds(angle);
}

///////////////////////   HuskyLens Test    ////////////////////
void HuskyLens_Test() {
  if (!huskylens.request(ID1)) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
  else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
  else Serial.println(F("HuskyLens OK!!!"));
}

///////////   Get Left and Right Distance per 50ms ///////////////
void Get_Distance() {
    if( millis() - DisTimer > 50) {
      LD = sonarL.ping_cm();    
      RD = sonarR.ping_cm();
      Serial.println( String() + F("LeftDistance = ") + LD);
      Serial.println( String() + F("RightDistance = ") + RD);
      DisTimer = millis();
    }    
}

////////////////////   Get yawAngle per 50 ms ////////////////////
void Get_yawAngle() {
  mpu.update();
  if ((millis() - MPUtimer) > 50) {
    if (start == false) {
      startAngle = abs(mpu.getAngleZ());
      Serial.println(startAngle);
    } else {
      yawAngle = abs(mpu.getAngleZ()) - startAngle;
      Serial.println( String() + F("YawAngle = ") + startAngle);
    }
    MPUtimer = millis();
  }
}
