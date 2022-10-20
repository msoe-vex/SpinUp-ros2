#pragma once
#include "auton/Auton.h"
#include "util/Timer.h"
#include "nodes/subsystems/IDriveNode.h"
#include "auton/auton_actions/DriveStraightAction.h"
#include "auton/auton_actions/TurnToAngleAction.h"
#include "nodes/odometry_nodes/OdometryNode.h"
#include "math/Math.h"

class testOdometry : public AutonAction {
private:
    Timer m_timer;
    IDriveNode* m_drive_node;
    OdometryNode* m_odom_node;

public:
    testOdometry(IDriveNode* drive_node, OdometryNode* odom_node);

    void ActionInit();

    actionStatus Action();
    
    void ActionEnd();
};