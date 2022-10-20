#pragma once

#include "Constants.h"
#include "auton/Auton.h"
#include "nodes/subsystems/IDriveNode.h"
#include "nodes/odometry_nodes/OdometryNode.h"
#include "nodes/sensor_nodes/InertialSensorNode.h"
#include "auton/auton_actions/DriveStraightAction.h"
#include "util/Constants.h"
#include "eigen/Eigen/Dense"

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