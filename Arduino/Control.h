#include <Arduino.h>
#include <PID_v1.h>


class Control
{
  private:
  double Setpoint1=0, Setpoint2=0, Input1, Output1, Input2, Output2; // Parameters for PID controller
  double Kpl = 0.3038 + 1, Kpp =  0.2971 + 1;   // Time constants of PID left(l) and right(p)
  double Kil = 2.7033 + 3.6, Kip = 2.9430 + 3.6;
  double Kdl =  0.0039 + 0.02, Kdp =  0.0037 + 0.02;

  PID *myPID1;
  PID *myPID2;
  
  public:
  Control(byte, byte);
  ~Control();

  void update_encoders(); //Function to reset encoder counters and save values of velocity
  float velocity_1,velocity_2;   //Data to storage velocity of both engines, public
  unsigned int encoder_counter_1, encoder_counter_2;
};
