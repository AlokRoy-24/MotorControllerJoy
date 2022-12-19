#include<ros.h>
#include<std_msgs/Int16.h>

ros::NodeHandle  nh;

int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

std_msgs::Int16 var_x;
ros::Publisher chatter_x("chatter_x", &var_x);

std_msgs::Int16 var_y;
ros::Publisher chatter_y("chatter_y", &var_x);

void setup() { 

  nh.initNode();
  nh.advertise(chatter_x);
  nh.advertise(chatter_y);
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  
}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, 255, -255);
  mapY = map(yPosition, 0, 1023, 255, -255);

  var_x.data=mapX;
  chatter_x.publish( &var_x);

  var_y.data=mapY;
  chatter_y.publish( &var_y);
  
  nh.spinOnce();
  delay(100);
  
}
