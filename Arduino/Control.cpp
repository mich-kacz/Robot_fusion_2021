#include "Control.h"


Control::Control(byte Pin_1, byte Pin_2)
{  
  myPID1 = new PID(&Input1, &Output1, &Setpoint1, Kpp, Kip, Kdp, DIRECT);
  myPID2 = new PID(&Input2, &Output2, &Setpoint2, Kpl, Kil, Kdl, DIRECT);

  myPID1->SetMode(AUTOMATIC);
  myPID2->SetMode(AUTOMATIC);
  myPID1->SetSampleTime(20);
  myPID2->SetSampleTime(20);
  
  pinMode(Pin_1, INPUT);
  pinMode(Pin_2, INPUT);
}



Control::~Control()
{
  delete myPID1;
  delete myPID2;
}



void Control::update_encoders()
{
  encoder_counter_1=0;
  encoder_counter_2=0;
  velocity_1 = (60*encoder_counter_1/(500*0.02));
  velocity_2 = (60*encoder_counter_2/(500*0.02));
}
