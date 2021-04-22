#include "Ros_comm.h"


Pub_Sub::Pub_Sub(ros::NodeHandle *nh_main, char pub_topic[15], char pub2_topic[15], char sub_topic[15]) : 
  chatter(pub_topic, &str_msg), 
  chatter2(pub2_topic, &range_msg), 
  sub(sub_topic, &Pub_Sub::callback, this)
{
  nh=nh_main;
  nh->advertise(chatter);
  nh->advertise(chatter2);
  nh->subscribe(sub);
}



void Pub_Sub::pub(float speed_left, float speed_right)
{
  str_msg.header.stamp = nh->now(); 
  str_msg.vector.x=speed_left;
  str_msg.vector.y=speed_right;
  str_msg.vector.z=0.2;
  chatter.publish(& str_msg);
  nh->spinOnce();
}



void Pub_Sub::pub_sensors(float data, float min_range, float max_range, char id[15])
{
  range_msg.range=data/100;
  range_msg.min_range=min_range/100;
  range_msg.max_range=max_range/100;
  range_msg.header.frame_id=id;     
  range_msg.header.stamp = nh->now(); 
  range_msg.radiation_type=0;       // Tutaj jest podana wartosc losowa mozna zmienic
  range_msg.field_of_view=5;       // Tutaj jest podana wartosc losowa mozna zmienic

  chatter2.publish(& range_msg);
  nh->spinOnce();
}



void Pub_Sub::callback(const geometry_msgs::Twist &msg)
{
  recv_msg.linear_x=msg.linear.x; 
  recv_msg.angular_z=msg.angular.z;    
}



void Pub_Sub::update_msgs()
{
  nh->spinOnce();
}



float Pub_Sub::get_message(char flag[1]) 
{
  if (flag=="x")
  {
    return recv_msg.linear_x;
  }
  else if (flag=="z")
  {
    return recv_msg.angular_z;
  }
  else
    return 0;
}



Pub_Sub::~Pub_Sub()
{
  /*str_msg.data="Arduino Bye";
  chatter.publish(& str_msg);
  nh->spinOnce();
  delay(5000);*/
}
