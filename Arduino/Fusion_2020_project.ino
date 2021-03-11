
#include "Ros_comm.h"

ros::NodeHandle nh;
Pub_Sub ross(&nh, "chatter", "sensors", "blinker");



void setup()
{
  nh.initNode();
  delay(2000); 
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
