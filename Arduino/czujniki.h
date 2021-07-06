#include <Arduino.h>

class Sensors{
  private:
    byte Bumper1, Bumper2, Bumper3, URECHO, URTRIG;
    double odl;
    const double p1=22.2;
    const double p2=-0.0004202;
    const double q1=-0.2385;
    const double q2=0.04675;
    const double multipler = 0.0049;
    unsigned int DistanceMeasured = 0;
    bool hit;

   public:
    double getRangeSHARP(int);
    void convertSHARP();
    unsigned int getRangeURT();
    bool getImpact();
    Sensors(byte, byte, byte, byte, byte);
    ~Sensors();
};
