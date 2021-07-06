/*Program is using + 7% of RAM because dynamic allocation*/


#define Enco_Pin_1 20 //Left encoder pin
#define Enco_Pin_2 21 //Right encoder pin


#include "Ros_comm.h"
#include "Control.h"
#include <Chrono.h>
#include "czujniki.h"


Chrono timer;
ros::NodeHandle nh;
Pub_Sub ross(&nh, "speed", "sensors", "cmd_vel");
Control cont(21, 20, 22, 23, 2, 3); //(encoder pins x2, Left_motor_direction, Right_motor_direction, Motor_left, Motor_right) <-- Pins

Sensors sensors(42, 44, 46, 34, 35);

float linear_vel_temp;


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
  
  //Here timer and senors + publishing  
  if(timer.hasPassed(20))
  {
    
    cont.update_encoders();

    
    if (linear_vel>=0)
      ross.pub((cont.velocity_1*0.10472*0.07), (cont.velocity_2*0.10472*0.07));
    else
      ross.pub((-cont.velocity_1*0.10472*0.07), (-cont.velocity_2*0.10472*0.07));

    linear_vel=ross.get_message("x");
    angular_vel=ross.get_message("z");

    ross.pub_sensors(cont.Setpoint1, 10, 80, "/ULTS1");
    ross.pub_sensors(cont.Setpoint2, 10, 80, "/ULTS2");
    
    
    timer.restart();
      
  }
  //End of timer and sensors + publishing
  
  if((sensors.getImpact() && linear_vel>0) || linear_vel==linear_vel_temp || (sensors.getRangeURT()<=30 && linear_vel>0))
  {
    cont.Motors_stop();
    linear_vel_temp=linear_vel;
  }
  else
  {
    linear_vel_temp=0.01;
    cont.update_pid(linear_vel, angular_vel);
  }
    
  
}
