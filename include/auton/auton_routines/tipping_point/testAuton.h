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

class testAuton : public Auton {
public:
    testAuton(ILiftNode* lift_node);

    void AddNodes();

private:
    ILiftNode* m_lift_node;

};