#include <ros/ros.h>
#include <urdf/model.h>
#include <sensor_msgs/JointState.h>

#include <iostream>


int main(int argc, char *argv[]) {
    ros::init(argc, argv, "joint_state_publisher");
    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);
    ros::Rate loop_rate(10);

    std::string urdf_file_name;
    urdf::Model model;
    if (n.getParam("robot_description", urdf_file_name)) {
        std::cout << "urdf_file_name:" << urdf_file_name << std::endl;
        if (!model.initString(urdf_file_name)) {
            ROS_ERROR("Failed to parse urdf file");
            return -1;
        }
    }

    std::vector<urdf::JointSharedPtr> joints;
    for (auto it = model.joints_.begin(); it != model.joints_.end(); it++) {
        urdf::JointSharedPtr joint = it->second;
        if (urdf::Joint::FIXED != joint->type) {
            joints.push_back(joint);
        }
    }

    double position = 0.0;
    while (ros::ok()) {
        sensor_msgs::JointState msg;
		msg.header.stamp = ros::Time::now();
        for (auto it = joints.begin(); it != joints.end(); it++) {
            msg.name.push_back((*it)->name);
            msg.position.push_back(position);
        }
        position = (position > 6.28) ? 0 : position + 0.01;

        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}