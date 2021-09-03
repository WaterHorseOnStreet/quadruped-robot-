#include <urdf/model.h>
#include <ros/ros.h>
#include <iostream>
        
int main(int argc, char *argv[]) {
    ros::init(argc, argv, "parser");
        
    if (2 != argc) {
        ROS_ERROR("Need a urdf file as argument");
        return -1;
    }
    std::string urdf_file_name = argv[1];
        
    urdf::Model model;
    if (!model.initFile(urdf_file_name)) {
        ROS_ERROR("Failed to parse urdf file");
        return -1;
    }
        
    std::cout << "Successfully parsed urdf file" << std::endl;
    std::cout << "机器人名称: " << model.getName() << std::endl;
    std::cout << "根节点: " << model.getRoot()->name << std::endl;
    std::cout << "根节点下有 " << model.getRoot()->child_joints.size() << "个关节" << std::endl;
    std::cout << "分别是:" << std::endl;
    for (int i = 0; i < model.getRoot()->child_joints.size(); i++)
        std::cout << model.getRoot()->child_joints[i]->name << std::endl;
       
    return 0;
}