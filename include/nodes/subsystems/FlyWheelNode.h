#pragma once

#include "nodes/NodeManager.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "util/PID.h"

class FlyWheelNode : public Node {
public:


    FlyWheelNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller,
    MotorNode motor);

    void initialize();

    void teleopPeriodicA();
    void teleopPeriodicB();

    void autonPeriodic();

    ~FlyWheelNode();

private:
    pros::Controller* m_controller;

    std::string m_handle_name;

    MotorNode* motor;

    PID* pid;

    bool toggle;


};