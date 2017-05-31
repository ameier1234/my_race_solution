//this is a comment

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

ros::Publisher pub;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  int size_of_range_array;
  int index_of_center;
  int left_bound;
  int right_bound;
  //float too_close;
  geometry_msgs::Twist twist;

  size_of_range_array = (msg->angle_max - msg->angle_min) / msg->angle_increment;
  //too_close = msg->range_min + ((msg->range_max - msg->range_min) / 4); 

  int i = 0;
  while(msg->ranges[i] != msg->range_max)
    {
      i++;
    }
  right_bound = i;
  while(msg->ranges[i] == msg->range_max)
    {
      i++;
    }
  left_bound = i;
  index_of_center = right_bound + ((left_bound - right_bound)/2);
  
  //ROS_INFO("greatest range index: %d\n", size_of_range_array);
  
  twist.angular.z = msg->angle_min + (msg->angle_increment * index_of_center);
  
  if(twist.angular.z > -0.35 && twist.angular.z < 0.35)
    {

      twist.linear.x = 4.99;
    }
  else 
    {
      twist.linear.x = 2.7;
    }

  pub.publish(twist);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "publisher");
  ros::init(argc, argv, "subscriber");
  ros::NodeHandle n;
  pub = n.advertise<geometry_msgs::Twist>("robot/cmd_vel", 1000);
  ros::Subscriber sub;

  sub = n.subscribe("robot/base_scan", 1000, chatterCallback);
  ros::spin();

   
  return 0;
}
