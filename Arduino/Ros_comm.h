/*How to use:
  1. Include Ros_comm.h in your main
  2. Create nodehandler in your main function
  3. Innit node by nh->initNode(); or nh.initNode(); in your main
  4. Create class passing to it parameters:address of nodehandler, topic name*/


#include<Arduino.h>
#include<ros.h>
#include <ros/time.h>
#include <geometry_msgs/Vector3Stamped.h>
#include<geometry_msgs/Twist.h>
#include<sensor_msgs/Range.h>


class Pub_Sub
{

  private:
  geometry_msgs::Vector3Stamped str_msg; // data for publishing floats
  ros::Publisher chatter, chatter2; //Publisher in contructor take parameters(topic name, address of data)
  ros::NodeHandle *nh; //Pointer for nodehandler in main function
  ros::Subscriber <geometry_msgs::Twist, Pub_Sub>sub; //Subscriber template takes (type of data, name of class)
  sensor_msgs::Range range_msg;//data for publishing sensors
  
  struct my_twist{float linear_x, angular_z;} recv_msg;

  void callback(const geometry_msgs::Twist &msg); //Callback function for subscriber
  
  public:
  Pub_Sub(ros::NodeHandle *nh_main, char [], char [], char []);//Contructor takes parameters(address of nodehandler, Topic names: 1.Pub floats 2.Pub range 3.Sub)
  ~Pub_Sub(); //Destructor is not doing antyhing yet
  void pub(float, float); //function for publishing data (from distance/?velocity? sensors)
  float get_message(char []); //Public function to get last message
  void update_msgs(); //Function to update incoming messages
  void pub_sensors(float, float, float, char []); //Publisher of range data type values(distance, min_range, max_range, frame_id)
  
};
