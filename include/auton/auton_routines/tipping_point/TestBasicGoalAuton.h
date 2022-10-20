#pragma once

#include "auton/Auton.h"
#include "nodes/subsystems/IDriveNode.h"
#include "nodes/subsystems/IClawNode.h"
#include "nodes/odometry_nodes/OdometryNode.h"
#include "auton/auton_actions/FollowPathAction.h"
#include "auton/auton_actions/UseClawAction.h"
#include "pathing/PathManager.h"
#include "pathing/Path.h"
#include "pursuit/path_pursuit/TankPathPursuit.h"
#include "eigen/Eigen/Dense"

class TestBasicGoalAuton : public Auton {
public:
    TestBasicGoalAuton(IDriveNode* drive_node, OdometryNode* odom_node, IClawNode* claw_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    IClawNode* m_claw_node;
    OdometryNode* m_odom_node;
    AutonNode* m_path_node;
    AutonNode* m_deploy_node;
    PathManager* m_path_manager;
};