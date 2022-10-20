#pragma once

#include "Constants.h"
#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/eigen/Eigen/Dense"

class tuningRoutine : public Auton {
public:
    tuningRoutine(IDriveNode* drive_node, OdometryNode* odometry_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    OdometryNode* m_odometry_node;

    AutonNode* m_forward_node;
    //AutonNode* m_backward_node;
};