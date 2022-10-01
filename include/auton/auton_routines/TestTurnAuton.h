#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/TurnToAngleAction.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/eigen/Eigen/Dense"

class TestTurnAuton : public Auton {
public:
    TestTurnAuton(IDriveNode* drive_node, InertialSensorNode* inertial_sensor_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    InertialSensorNode* m_inertial_sensor_node;
    AutonNode* m_turn_node;
};