#pragma once

#include "nodes/NodeManager.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "util/PID.h"

class FlyWheelNode : public Node {
public:


    FlyWheelNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller,
    MotorNode* motorL, MotorNode* motorR);

    void initialize();

    void teleopPeriodic();
    void teleopPeriodicB();

    void autonPeriodic();

    ~FlyWheelNode();

private:
    pros::Controller* m_controller;

    std::string m_handle_name;

    MotorNode* m_motorL;
    MotorNode* m_motorR;

    PID* m_pid;

    bool m_toggle;


};