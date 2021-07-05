#include <Wire.h>
#include <Servo.h>
int i =0 ;
byte data =0;
Servo right_prop;
Servo left_prop;
 
/*MPU-6050 gives you 16 bits data so you have to create some 16int constants
 * to store the data for accelerations and gyro*/

int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;
 

float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];




float elapsedTime, time, timePrev;
 
float rad_to_deg = 180/3.141592654;

float PID, pwmLeft, pwmRight, error, previous_error;
float pid_p=0;
float pid_i=0;
float pid_d=0;
/////////////////PID CONSTANTS/////////////////
double kp= 1.1;//0.8; //// 4.17;        //3.00;//3.55
double ki=0.004; //0.003;//0.001; //0.005;       //0.005;//0.003
double kd=0.8; //1 ;//0.3;   //13 ;        //5.05;//2.05
///////////////////////////////////////////////

double throttle=1250; //initial value of throttle to the motors
float desired_angle = 0; //This is the angle in which we whant the
                         //balance to stay steady


void setup() {
  Wire.begin(); //begin the wire comunication
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(57600);
  right_prop.attach(3); //attatch the right motor to pin 3
  left_prop.attach(5);  //attatch the left motor to pin 5

  time = millis(); //Start counting time in milliseconds 
  left_prop.writeMicroseconds(1000); 
  right_prop.writeMicroseconds(1000);
  delay(7000); /*Give some delay, 7s, to have time to connect
                *the propellers and let everything start up*/ 
}//end of setup void
void loop() {
/////////////////////////////I M U/////////////////////////////////////
   // timePrev = time;  // the previous time is stored before the actual time read
   // time = millis();  // actual time read
   // elapsedTime = (time - timePrev) / 1000; 
    /////////// vong PID loop nay se dc goi ra 10ms 1 lan. no se tinh goc lech va PID
    if(millis() - timePrev >=10)
    {
     Wire.beginTransmission(0x68);
     Wire.write(0x3B); //Ask for the 0x3B register- correspond to AcX
     Wire.endTransmission(false);
     Wire.requestFrom(0x68,6,true);  
     Acc_rawX=Wire.read()<<8|Wire.read(); //each value needs two registres
     Acc_rawY=Wire.read()<<8|Wire.read();
     Acc_rawZ=Wire.read()<<8|Wire.read();
 
     /*---X---*/
  //   Acceleration_angle[0] = atan((Acc_rawY/16384.0)/sqrt(pow((Acc_rawX/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
     /*---Y---*/
     Acceleration_angle[1] = atan(-1*(Acc_rawX/16384.0)/sqrt(pow((Acc_rawY/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
 
   Wire.beginTransmission(0x68);
   Wire.write(0x43); //Gyro data first adress
   Wire.endTransmission(false);
   Wire.requestFrom(0x68,4,true); //Just 4 registers
   
   Gyr_rawX=Wire.read()<<8|Wire.read(); //Once again we shif and sum
   Gyr_rawY=Wire.read()<<8|Wire.read();
   /*---X---*/
//   Gyro_angle[0] = Gyr_rawX/131.0; 
   /*---Y---*/
   Gyro_angle[1] = Gyr_rawY/131.0;
   /*---X axis angle---*/
//   Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*elapsedTime) + 0.02*Acceleration_angle[0];
   /*---Y axis angle---*/
   Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*0,04) + 0.02*Acceleration_angle[1];
   
   /*Now we have our angles in degree and values from -10Âº0 to 100Âº aprox*/
    Serial.println(Total_angle[1]);
 
error = Total_angle[1] - desired_angle;
 
pid_p = kp*error;
 
if(-3 <error <3)
{
  pid_i = pid_i+(ki*error);  
} 
pid_d = kd*((error - previous_error)/0.01);

/*The final PID values is the sum of each of this 3 parts*/
PID = pid_p + pid_i + pid_d;
 
if(PID < -1000)
{
  PID=-1000;
}
if(PID > 1000)
{
  PID=1000;
}
 
pwmLeft = throttle + PID;
pwmRight = throttle - PID;
 
//Right
if(pwmRight < 1000)
{
  pwmRight= 1000;
}
if(pwmRight > 1500)
{
  pwmRight=1500;
}
//Left
if(pwmLeft < 1000)
{
  pwmLeft= 1000;
}
if(pwmLeft > 1500)
{
  pwmLeft=1500;
}
timePrev = millis();
previous_error = error;
    }
///////////// DK dong co///////////////////
if(millis()<=60000)
   {  
  left_prop.writeMicroseconds(pwmLeft);
  right_prop.writeMicroseconds(pwmRight);
   }
else {
  left_prop.writeMicroseconds(0);
  right_prop.writeMicroseconds(0);
  }
//previous_error = error; //Remember to store the previous error.

}//end of loop void

