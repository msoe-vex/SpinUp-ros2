#pragma once

#include "nodes/NodeManager.h"
#include "api.h"

class MotorNode : public Node {
private:
    pros::Motor m_motor;
    std::string m_handle_name;

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
