#include "czujniki.h"
Sensors::Sensors(byte Bumper_1, byte Bumper_2, byte Bumper_3, byte Urecho, byte URtrig)
{
  pinMode(Bumper_1, INPUT);  
  pinMode(Bumper_2, INPUT);  
  pinMode(Bumper_3, INPUT);

  Bumper1=Bumper_1;
  Bumper2=Bumper_2;
  Bumper3=Bumper_3;
  URECHO=Urecho;
  URTRIG=URtrig;
    
  pinMode(URTRIG, OUTPUT);
  digitalWrite(URTRIG, HIGH); 
  pinMode(URECHO, INPUT);  
}

Sensors::~Sensors(){}

double Sensors::getRangeSHARP(int id){
  odl = analogRead(id);
  convertSHARP();
  if (odl > 80)
    odl = 1000;
  else if (odl < 10)
    odl = 0;
  return odl;
}

void Sensors::convertSHARP (){
  odl = odl*multipler;
  odl = (p1*odl + p2)/(odl*odl + q1*odl + q2);
}

unsigned int Sensors::getRangeURT(){
  
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  unsigned long LowLevelTime = pulseIn(URECHO, LOW) ;
  if (LowLevelTime >= 50000)
    DistanceMeasured = 100000;
  else
    DistanceMeasured = LowLevelTime / 50;
  return DistanceMeasured;
}

bool Sensors::getImpact(){
  
  if(!digitalRead(Bumper1) || !digitalRead(Bumper2) || !digitalRead(Bumper3))
  { 
    return true;
  }
  else
    return false;
  
}
