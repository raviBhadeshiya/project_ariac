#include <algorithm>
#include <vector>
#include <cmath>
#include <ros/ros.h>
 
#include <osrf_gear/LogicalCameraImage.h>
#include <osrf_gear/VacuumGripperControl.h>
#include <osrf_gear/AGVControl.h>
#include <osrf_gear/Order.h>
#include <osrf_gear/Proximity.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_srvs/Trigger.h>
#include <trajectory_msgs/JointTrajectory.h>

#include <moveArm.hpp>
#include <manageOrder.hpp>

/// Start the competition by waiting for and then calling the start ROS Service.
void start_competition(ros::NodeHandle & node) {
   // Create a Service client for the correct service, i.e. '/ariac/start_competition'.
   ros::ServiceClient start_client =
     node.serviceClient<std_srvs::Trigger>("/ariac/start_competition");
   // If it's not already ready, wait for it to be ready.
   // Calling the Service using the client before the server is ready would fail.
   if (!start_client.exists()) {
     ROS_INFO("Waiting for the competition to be ready...");
     start_client.waitForExistence();
     ROS_INFO("Competition is now ready.");
   }
   ROS_INFO("Requesting competition start...");
   std_srvs::Trigger srv;  // Combination of the "request" and the "response".
   start_client.call(srv);  // Call the start Service.
   if (!srv.response.success) {  // If not successful, print out why.
     ROS_ERROR_STREAM("Failed to start the competition" << srv.response.message);
   }
 }

void send_order(ros::NodeHandle & node) {
   // Create a Service client for the correct service, i.e. '/ariac/start_competition'.
   ros::ServiceClient agv_client =
     node.serviceClient<osrf_gear::AGVControl>("/ariac/agv1");
   // If it's not already ready, wait for it to be ready.
   // Calling the Service using the client before the server is ready would fail.
   if (!agv_client.exists()) {
     ROS_INFO("Waiting for the AGV client to be ready...");
     agv_client.waitForExistence();
     ROS_INFO("AGV client is now ready.");
   }
   ROS_INFO("Requesting AGV to complete order...");
   osrf_gear::AGVControl srv;  // Combination of the "request" and the "response".
   srv.request.kit_type = 'order_0_kit_0'; 
   agv_client.call(srv);  // Call the start Service.
   if (!srv.response.success) {  // If not successful, print out why.
     ROS_ERROR_STREAM("Failed to start the competition");
   }
 }

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ariac_qual1");
    ros::NodeHandle nh;                                 // standard ros node handle
    moveArm robotArm(nh);
    std::vector<double> my_pose = robotArm.getJointsState();
    start_competition(nh);
    ROS_INFO("Competition started!");
    manageOrder order1(nh);
    std::vector<geometry_msgs::TransformStamped> tf = order1.getTransform();
    for(auto pose: tf) {
       ROS_INFO("Translation: %f, %f, %f", pose.transform.translation.x
          , pose.transform.translation.y, pose.transform.translation.z);
       ROS_INFO("Rotation: %f, %f, %f, %f", pose.transform.rotation.x
          , pose.transform.rotation.y, pose.transform.rotation.z, pose.transform.rotation.w);  
    }
    ros::Duration(2).sleep();
    
    // pick the 1st part
    // my_pose = {1.765,0.514,-0.446,2.998,3.387,-1.509,-0.13};
    my_pose = {1.746341859700843, 0.4499279733031516, -0.43302049465225334, 3.087641902710679, 3.3455451498737525, -1.5251158851790891, -0.09422732907569387};
    robotArm.sendJointsValue(my_pose);
    robotArm.grab();
    robotArm.waitForGripperAttach(1.0);

    // move to the tray and drop
    robotArm.movetoTray("piston");
         
    // move back to the bin and pick 2nd part
    robotArm.movetoBin();
    // my_pose = {2.09,-0.076,-0.48,3.52,3.06,-1.52,0.34};
    my_pose = {1.9993150258725745, 0.8283612304111034, -0.47862158150121203, 2.564217444355852, 3.1302356236171165, -1.5201078533494, -0.590161088164975};
    robotArm.sendJointsValue(my_pose);
    robotArm.grab();
    robotArm.waitForGripperAttach(1.0);

    // move to the tray and drop
    robotArm.movetoTray("gear");

    // move back to the bin and pick 3rd part
    robotArm.movetoBin();
    //my_pose = {2.108,0.473,-0.480,3.132,3.083,-1.520,-0.0399};
    my_pose = {1.746341859700843, 0.4499279733031516, -0.43302049465225334, 3.087641902710679, 3.3455451498737525, -1.5251158851790891, -0.09422732907569387};
    robotArm.sendJointsValue(my_pose);
    robotArm.grab();
    robotArm.waitForGripperAttach(1.0);

    // move to the tray and drop
    robotArm.movetoTray("piston");
    my_pose = {1.7556661913415947, 0.8258945923604798, -0.4462087335570226, 2.6438218578458903, 3.393951279745265, -1.5038396922932926, -0.5269700067425571};
    // move back to the bin and pick 4th part
    robotArm.movetoBin();
    // my_pose = {1.961,-0.317,-0.477,3.317,3.223,-1.519,0.145};

    robotArm.sendJointsValue(my_pose);
    robotArm.grab();
    robotArm.waitForGripperAttach(1.0);
        
    // move to the tray and drop
    robotArm.movetoTray("gear");

    // move back to the bin and pick 5th part
    robotArm.movetoBin();
    // my_pose = {1.953,-0.421,-0.481,3.35,3.234,-1.519,0.177};
    my_pose = {1.7795219161302143, 0.7201174188260127, -0.44470612613149196, 2.6770752858142997, 3.304222564211552, -1.5372031877129149, -0.44807671536402083};
    robotArm.sendJointsValue(my_pose);
    robotArm.grab();
    robotArm.waitForGripperAttach(1.0);
     
    // move to the tray and drop
    robotArm.movetoTray("gear");

    // move the arm back to its original position
    robotArm.movetoBin();
    my_pose = {1.512,0.000,-1.12,3.138,3.767,-1.506,0.000};
    robotArm.sendJointsValue(my_pose);
    ros::Duration(1.0).sleep();

    // send the agv1 to complete order
    send_order(nh);
    return 0;
}
