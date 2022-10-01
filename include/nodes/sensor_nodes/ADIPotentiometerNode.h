#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/Float64.h"
#include "ros_lib/std_msgs/Empty.h"

class ADIPotentiometerNode : public Node {
private:
    pros::ADIPotentiometer m_potentiometer;
    std_msgs::Float64 m_potentiometerMsg;
    std::string m_handleName;
    std::string m_subPublishDataName;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, ADIPotentiometerNode>* m_publishDataSub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    ADIPotentiometerNode(NodeManager* node_manager, int port, std::string handle_name, pros::adi_potentiometer_type_e pot_type=pros::E_ADI_POT_EDR);

    ADIPotentiometerNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair, std::string handle_name, pros::adi_potentiometer_type_e pot_type=pros::E_ADI_POT_EDR);

    void initialize();

    int getValue();

    double getAngle();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIPotentiometerNode();
};
