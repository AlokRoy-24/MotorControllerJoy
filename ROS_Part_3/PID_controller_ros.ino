#include<ros.h>
#include<std_msgs/Int16.h>
#include<std_msgs/Int32.h>

ros::NodeHandle  nh;

int RPM_VALUE_X=0;        // for spped measuring of X_Motor
long int time_start_x;
long int time_end_x;
int count_x=0;
  
int RPM_VALUE_Y=0;        // for spped measuring of Y_Motor
long int time_start_y;
long int time_end_y;
int count_y=0;



int VRx = A0;              //for joystick
int VRy = A1;

int xPosition = 0;         //jostick variables
int yPosition = 0;
int mapX = 0;
int mapY = 0;

int enX = 9;              // Motor X connections
int in1 = 8;
int in2 = 7;

int enY = 10;             // Motor Y connections
int in3 = 5;
int in4 = 4;


std_msgs::Int16 var_x;                              //ros connection for jostick
ros::Publisher chatter_x("chatter_x", &var_x);

std_msgs::Int16 var_y;                                //ros connection for jostick
ros::Publisher chatter_y("chatter_y", &var_y);

std_msgs::Int16 rpm_x;                             
ros::Publisher chatter_rpm_x("rpm_x", &rpm_x);

std_msgs::Int16 rpm_y;                             
ros::Publisher chatter_rpm_y("rpm_y", &rpm_y);

std_msgs::Int32 delta_time;                             
ros::Publisher chatter_delta_time("time_int", &delta_time);

void run_motorx(const std_msgs::Int16& data){
  int pwm=data.data;
  if(pwm>255){
    pwm=255;
  }
  if(pwm>0){
    analogWrite(enX,pwm);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else{
    analogWrite(enX,(pwm*-1));
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
}

void run_motory(const std_msgs::Int16& data){
  int pwm=data.data;
  if(pwm>255){
    pwm=255;
  }
  if(pwm>0){
    analogWrite(enY,pwm);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else{
    analogWrite(enY,(pwm*-1));
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

ros::Subscriber<std_msgs::Int16>sub_x("motor_x",run_motorx);
ros::Subscriber<std_msgs::Int16>sub_y("motor_y",run_motory); 

void setup() { 

  nh.initNode();
  nh.advertise(chatter_x);
  nh.advertise(chatter_y);
  nh.advertise(chatter_rpm_x);
  nh.advertise(chatter_rpm_y);
  nh.advertise(chatter_delta_time);
  nh.subscribe(sub_x);
  nh.subscribe(sub_y);

  pinMode(enX, OUTPUT);         // Set all the motor control pins to outputs
  pinMode(enY, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  digitalWrite(in1, LOW);      // Turn off motors - Initial state
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  
}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  mapX = map(xPosition, 0, 1023, 255, -255);
  mapY = map(yPosition, 0, 1023, 255, -255);

  var_x.data=mapX;
  chatter_x.publish( &var_x);

  var_y.data=mapY;
  chatter_y.publish( &var_y);

  attachInterrupt(digitalPinToInterrupt(2),speed_x, RISING);
  attachInterrupt(digitalPinToInterrupt(3),speed_y, RISING);
  
  nh.spinOnce();
  delay(100);
  
}

void speed_x()
{
 if(count_x==0){
  time_start_x=micros();
  count_x++;
 }
 else{
  time_end_x=micros();
  RPM_VALUE_X=(60*1000000)/(time_end_x-time_start_x);
  delta_time.data=(time_end_x-time_start_x)*1000000;
  chatter_delta_time.publish( &delta_time);
  if(RPM_VALUE_X>0 && RPM_VALUE_X<1000){
    rpm_x.data=RPM_VALUE_X;
    chatter_rpm_x.publish(& rpm_x);
  }
  count_x=0;
 }
}

void speed_y()
{
 if(count_y==0){
  time_start_y=micros();
  count_y++;
 }
 else{
  time_end_y=micros();
  RPM_VALUE_Y=(60*1000000)/(time_end_y-time_start_y);
  if(RPM_VALUE_Y>0 && RPM_VALUE_Y<1000){
    rpm_y.data=RPM_VALUE_Y;
    chatter_rpm_y.publish(& rpm_y);
  }
  count_y=0;
 }
}
