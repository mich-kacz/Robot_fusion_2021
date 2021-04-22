#include "Control.h"


Control::Control(byte Pin_1, byte Pin_2, byte M1_dir, byte M2_dir, byte M1, byte M2)
{  
  myPID1 = new PID(&Input1, &Output1, &Setpoint1, Kpp, Kip, Kdp, DIRECT);
  myPID2 = new PID(&Input2, &Output2, &Setpoint2, Kpl, Kil, Kdl, DIRECT);

  myPID1->SetMode(AUTOMATIC);
  myPID2->SetMode(AUTOMATIC);
  myPID1->SetSampleTime(20);
  myPID2->SetSampleTime(20);
  
  pinMode(Pin_1, INPUT);
  pinMode(Pin_2, INPUT);
  M1_direction=M1_dir;
  M2_direction=M2_dir;
  Motor1=M1;
  Motor2=M2;
}



Control::~Control()
{
  delete myPID1;
  delete myPID2;
}



void Control::update_encoders()
{
  encoder_counter_1=0; //Left encoder
  encoder_counter_2=0; //Right encoder
  velocity_1 = (60*encoder_counter_1/(500*0.02)); //Left
  velocity_2 = (60*encoder_counter_2/(500*0.02)); //Right
}



void Control::update_pid(float linear_vel, float angular_vel)
{
  if (linear_vel<0)
  {
    linear_vel=abs(linear_vel);
    digitalWrite(M1_direction, HIGH); // Robot goes back
    digitalWrite(M2_direction, HIGH);
  }
  else
  {
    digitalWrite(M1_direction, LOW); // Robot goes forward
    digitalWrite(M2_direction, LOW);
  }
  
  Setpoint1=(2*linear_vel-track_width*angular_vel)/wheel_diameter; //Left wheel
  Setpoint2=(2*linear_vel+track_width*angular_vel)/wheel_diameter; //Right wheel

  Input1 = velocity_1;
  Input2 = velocity_2;

  myPID1->Compute();
  myPID2->Compute();

  analogWrite(Motor1,Output1); //lewy
  analogWrite(Motor2,Output2); //prawy
  
}
