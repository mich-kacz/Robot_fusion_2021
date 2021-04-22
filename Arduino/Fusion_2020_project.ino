/*Program is using + 7% of RAM because dynamic allocation*/


#define Enco_Pin_1 2 //Left encoder pin
#define Enco_Pin_2 3 //Right encoder pin


#include "Ros_comm.h"
#include "Control.h"
#include <Chrono.h>


Chrono timer;
ros::NodeHandle nh;
Pub_Sub ross(&nh, "chatter", "sensors", "blinker");
Control cont(2,3, 4, 5, 6, 7); //(encoder pins x2, Left_motor_direction, Right_motor_direction, Motor_left, Motor_right) <-- Pins



void enco_callback1()
{
  cont.encoder_counter_1++; //Left encoder
}

void enco_callback2()
{
  cont.encoder_counter_2++; //Right encoder
}



void setup()
{
  nh.initNode();

  attachInterrupt(digitalPinToInterrupt(Enco_Pin_1), enco_callback1, FALLING); //Left encoder
  attachInterrupt(digitalPinToInterrupt(Enco_Pin_2), enco_callback2, FALLING); //Right encoder
  
  delay(500); 
  timer.restart();
}



void loop()
{ 
  float linear_vel, angular_vel;

  ross.update_msgs();
  linear_vel=ross.get_message("x");
  angular_vel=ross.get_message("z");
  
  //Here timer and senors + publishing  
  if(timer.hasPassed(20))
  {
    cont.update_encoders();
  
    ross.pub(cont.velocity_1);
    ross.pub(cont.velocity_2);
    
    ross.pub_sensors(50, 10, 80, "IFR_1");
    
  }
  //End of timer and sensors + publishing
  

  cont.update_pid(linear_vel, angular_vel);
  
}
