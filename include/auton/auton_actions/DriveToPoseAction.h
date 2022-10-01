#pragma once

#include <math.h>
#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/pursuit/pose_pursuit/IPosePursuit.h"
#include "lib-rr/math/Pose.h"

class DriveToPoseAction : public AutonAction {
private:
    IDriveNode* m_drive_node;
    OdometryNode* m_odom_node;
    IPosePursuit* m_pursuit;
    Timer m_timer;
    Pose m_end_pose;

public:
    DriveToPoseAction(IDriveNode* drive_node, OdometryNode* odom_node, IPosePursuit* pursuit, Pose end_pose);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};