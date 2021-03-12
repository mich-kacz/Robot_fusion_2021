/*Program is using + 7% of RAM because dynamic allocation*/


#define Enco_Pin_1 2
#define Enco_Pin_2 3


#include "Ros_comm.h"
#include "Control.h"


ros::NodeHandle nh;
Pub_Sub ross(&nh, "chatter", "sensors", "blinker");
Control cont(2,3);



void enco_callback1()
{
  cont.encoder_counter_1++;
}

void enco_callback2()
{
  cont.encoder_counter_2++;
}



void setup()
{
  nh.initNode();

  attachInterrupt(digitalPinToInterrupt(Enco_Pin_1), enco_callback1, FALLING);
  attachInterrupt(digitalPinToInterrupt(Enco_Pin_2), enco_callback2, FALLING);
  
  delay(500); 
}



void loop()
{ 
  float temp;

  ross.update_msgs();
  temp=ross.get_message("x");
  ross.pub(temp);
  delay(500);
  ross.pub_sensors(50, 10, 80, "IFR_1");
  delay(500);
}
