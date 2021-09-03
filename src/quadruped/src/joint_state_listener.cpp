#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <iostream>
        
void callback(const sensor_msgs::JointState::ConstPtr &msg) {
    std::cout << "===========================================================================" << std::endl;
    std::cout << msg->name.size() << "\t" << msg->position.size() << "\t";
    std::cout << msg->velocity.size() << "\t" << msg->effort.size() << std::endl;
    int n = msg->name.size();
    for (int i = 0; i < n; i++) {
        std::cout << msg->name[i] << ":" << msg->position[i] << std::endl;
    }
}
        
int main(int argc, char *argv[]) {
    ros::init(argc, argv, "joint_state_listener");
    ros::NodeHandle n;
        
    ros::Subscriber sub = n.subscribe("joint_states", 1000, callback);
    ros::spin();
}
