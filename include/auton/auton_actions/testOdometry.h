#pragma once
#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "lib-rr/auton/auton_actions/TurnToAngleAction.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/math/Math.h"

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