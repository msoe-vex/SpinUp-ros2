#pragma once

#include "auton/Auton.h"
#include "nodes/subsystems/IDriveNode.h"
#include "nodes/odometry_nodes/OdometryNode.h"
#include "nodes/sensor_nodes/InertialSensorNode.h"
#include "auton/auton_actions/DriveStraightAction.h"
#include "auton/auton_actions/testOdometry.h"
#include "auton/auton_actions/UseClawAction.h"
#include "auton/auton_actions/MoveLiftToPositionAction.h"
#include "util/Constants.h"
#include "eigen/Eigen/Dense"

class odomTest : public Auton {
public:
    odomTest(IDriveNode* drive_node, OdometryNode* odom_node, InertialSensorNode* inertial_sensor_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    OdometryNode* m_odom_node;
    InertialSensorNode* m_inertial_sensor_node;

};