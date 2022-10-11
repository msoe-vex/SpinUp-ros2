#pragma once

#include "auton/Auton.h"
#include "nodes/subsystems/IDriveNode.h"
#include "nodes/odometry_nodes/OdometryNode.h"
#include "auton/auton_actions/DriveToPoseAction.h"
#include "pursuit/pose_pursuit/HolonomicPosePursuit.h"
#include "eigen/Eigen/Dense"

class TestPoseAuton : public Auton {
public:
    TestPoseAuton(IDriveNode* drive_node, OdometryNode* odom_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    OdometryNode* m_odom_node;
    AutonNode* m_pose_node;
};