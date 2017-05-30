#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

ros::Publisher pub;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  geometry_msgs::Twist twist;
  twist.angular.x = 2;
  twist.angular.y = 0;
  twist.angular.z = 0;
  pub.publish(twist);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "subscriber");
  ros::NodeHandle n;
  pub = n.advertise<geometry_msgs::Twist>("robot/cmd_vel", 1000);
  ros::Subscriber sub;

  while(ros::ok())
  {
     sub = n.subscribe("robot/base_scan", 1000, chatterCallback);
     ros::spinOnce();

  } 
  return 0;
}
