#pragma once

#include "auton/Auton.h"
#include "nodes/subsystems/IDriveNode.h"
#include "nodes/sensor_nodes/InertialSensorNode.h"
#include "auton/auton_actions/TurnToAngleAction.h"
#include "util/Constants.h"
#include "eigen/Eigen/Dense"

class TestTurnAuton : public Auton {
public:
    TestTurnAuton(IDriveNode* drive_node, InertialSensorNode* inertial_sensor_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    InertialSensorNode* m_inertial_sensor_node;
    AutonNode* m_turn_node;
};