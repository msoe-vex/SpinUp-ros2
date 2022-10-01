#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/auton/auton_actions/DriveToPoseAction.h"
#include "lib-rr/pursuit/pose_pursuit/HolonomicPosePursuit.h"
#include "lib-rr/eigen/Eigen/Dense"

class TestPoseAuton : public Auton {
public:
    TestPoseAuton(IDriveNode* drive_node, OdometryNode* odom_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    OdometryNode* m_odom_node;
    AutonNode* m_pose_node;
};