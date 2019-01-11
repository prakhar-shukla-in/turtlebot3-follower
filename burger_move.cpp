#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
ros::Publisher velocity_publisher;
void calculate_distance(double distance);
//method to move robot straight
void move(double speed,double distance,bool isForward);
void move1(double speed,double distance,bool isForward);
void move2(double speed,double distance,bool isForward);
void rotate1 (double angular_speed, double angle, bool clockwise);
void rotate2 (double angular_speed, double angle, bool clockwise);


int main(int argc,char **argv)
{

  ros::init(argc,argv,"turtle_node");
  ros::NodeHandle n;

  velocity_publisher=n.advertise<geometry_msgs::Twist>("/cmd_vel",10);

  move(2.0,28.6,1);
  rotate1(2.174,1.4,0);  //ros understand radian so angular velocity in radian per sec and angle in radian
  move1(2.0,8,1);  
  rotate2(2.174,1.4,1); // as 10 deg is 0.174 radians
  move2(2.0,28.6,1);
  rotate2(2.174,1.4,1);
  move1(2.0,8,1);
}

void move(double speed,double distance,bool isForward){

  geometry_msgs::Twist vel_msg;
  if(isForward)
   vel_msg.linear.x=abs(speed);
  else
   vel_msg.linear.x=-abs(speed);
   vel_msg.linear.y=0;
   vel_msg.linear.z=0;
  
  //we set a random angular velocity in the y-axis
   vel_msg.angular.x=0;
   vel_msg.angular.y=0;
   vel_msg.angular.z=1;
   
  //to:current time
  double t0=ros::Time::now().toSec();
  double current_distance=0;
  ros::Rate loop_rate(100); //100 messeges per second is sent (to make it more accurate)
  //loop to publish the messege
  do{
      velocity_publisher.publish(vel_msg);
      double t1=ros::Time::now().toSec();
      current_distance=speed * (t1-t0);
      ros::spinOnce();
      loop_rate.sleep();
    }while(current_distance < distance);
    calculate_distance(current_distance/4.55);
    vel_msg.linear.x=0;
    vel_msg.linear.y=0;
    vel_msg.linear.z=0;
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;
    vel_msg.angular.z=0;
    velocity_publisher.publish(vel_msg);
  //publish the velocity
  //estimate the distance=speed * (t1-t0)
  //current_distance_moved_by_robot <= distance
}

void move1(double speed,double distance,bool isForward){

  geometry_msgs::Twist vel_msg;
  if(isForward)
   vel_msg.linear.x=abs(speed);
  else
   vel_msg.linear.x=-abs(speed);
   vel_msg.linear.y=0;
   vel_msg.linear.z=0;
  
  //we set a random angular velocity in the y-axis
   vel_msg.angular.x=0;
   vel_msg.angular.y=0;
   vel_msg.angular.z=0;
   
  //to:current time
  double t0=ros::Time::now().toSec();
  double current_distance=0;
  ros::Rate loop_rate(100); //100 messeges per second is sent
  //loop to publish the messege
  do{
      velocity_publisher.publish(vel_msg);
      double t1=ros::Time::now().toSec();
      current_distance=speed * (t1-t0);
      ros::spinOnce();
      loop_rate.sleep();
    }while(current_distance < distance);
    calculate_distance(current_distance/8);
    vel_msg.linear.x=0;
    vel_msg.linear.y=0;
    vel_msg.linear.z=0;
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;
    vel_msg.angular.z=0;
 
    velocity_publisher.publish(vel_msg);
  //publish the velocity
  //estimate the distance=speed * (t1-t0)
  //current_distance_moved_by_robot <= distance
}
void move2(double speed,double distance,bool isForward){

  geometry_msgs::Twist vel_msg;
  if(isForward)
   vel_msg.linear.x=abs(speed);
  else
   vel_msg.linear.x=-abs(speed);
   vel_msg.linear.y=0;
   vel_msg.linear.z=0;
  
  //we set a random angular velocity in the y-axis
   vel_msg.angular.x=0;
   vel_msg.angular.y=0;
   vel_msg.angular.z=-1;
   
  //to:current time
  double t0=ros::Time::now().toSec();
  double current_distance=0;
  ros::Rate loop_rate(100); //100 messeges per second is sent
  //loop to publish the messege
  do{
      velocity_publisher.publish(vel_msg);
      double t1=ros::Time::now().toSec();
      current_distance=speed * (t1-t0);
      ros::spinOnce();
      loop_rate.sleep();
    }while(current_distance < distance);
    calculate_distance(current_distance/4.55);
    vel_msg.linear.x=0;
    vel_msg.linear.y=0;
    vel_msg.linear.z=0;
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;
    vel_msg.angular.z=0;

    velocity_publisher.publish(vel_msg);
  //publish the velocity
  //estimate the distance=speed * (t1-t0)
  //current_distance_moved_by_robot <= distance
}

void rotate1 (double angular_speed, double relative_angle, bool clockwise){

	geometry_msgs::Twist vel_msg;
	//set a random linear velocity in the x-axis
	vel_msg.linear.x =0;
	vel_msg.linear.y =0;
	vel_msg.linear.z =0;
	//set a random angular velocity in the y-axis
	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;

	if (clockwise)
		vel_msg.angular.z =-abs(angular_speed);
	else
		vel_msg.angular.z =abs(angular_speed);

	double current_angle = 0.0;
	double t0 = ros::Time::now().toSec(); //time before entering the loop
	ros::Rate loop_rate(10); //10 times per second
	do{
		velocity_publisher.publish(vel_msg); //keep publishing the messege while curr angle is smaller than relative angle
		double t1 = ros::Time::now().toSec(); //current tym measured inside the loop
		current_angle = angular_speed * (t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	}while(current_angle<relative_angle);

	vel_msg.angular.z =0; //for stopping the robot
	velocity_publisher.publish(vel_msg);

}

void rotate2 (double angular_speed, double relative_angle, bool clockwise){

	geometry_msgs::Twist vel_msg;
	//set a random linear velocity in the x-axis
	vel_msg.linear.x =0;
	vel_msg.linear.y =0;
	vel_msg.linear.z =0;
	//set a random angular velocity in the y-axis
	vel_msg.angular.x = 0;
	vel_msg.angular.y = 0;

	if (clockwise)
		vel_msg.angular.z =-abs(angular_speed);
	else
		vel_msg.angular.z =abs(angular_speed);

	double current_angle = 0.0;
	double t0 = ros::Time::now().toSec();
	ros::Rate loop_rate(10);
	do{
		velocity_publisher.publish(vel_msg);
		double t1 = ros::Time::now().toSec();
		current_angle = angular_speed * (t1-t0);
		ros::spinOnce();
		loop_rate.sleep();
	}while(current_angle<relative_angle);

	vel_msg.angular.z =0;
	velocity_publisher.publish(vel_msg);

}
void calculate_distance(double distance){
static int total_distance;
total_distance+=distance;
ROS_INFO("%d ", total_distance);
}
