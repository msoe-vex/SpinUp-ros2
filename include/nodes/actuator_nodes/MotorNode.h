#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/v5_hal/V5Motor.h"
#include "ros_lib/std_msgs/Int8.h"
#include "ros_lib/std_msgs/Empty.h"

class MotorNode : public Node {
private:
    pros::Motor m_motor;
    v5_hal::V5Motor m_motor_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    std::string m_sub_move_motor_voltage_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Int8, MotorNode>* m_move_motor_voltage_sub;
    ros::Subscriber<std_msgs::Empty, MotorNode>* m_publish_data_sub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

    void m_moveMotorVoltage(const std_msgs::Int8& msg);

    int m_getMaxRPM();

public:
    MotorNode(NodeManager* node_manager, int port_number, std::string handle_name,
        bool reverse=false, pros::motor_gearset_e_t gearset=pros::E_MOTOR_GEARSET_18);

    void initialize();

    pros::Motor* getMotor();

    void resetEncoder();

    int getPosition();

    void move(int value);

    void moveVoltage(int voltage);

    void moveVelocity(float velocity);

    void moveAbsolute(double position, int max_velocity);

    void teleopPeriodic();

    void autonPeriodic();

    ~MotorNode();
};
