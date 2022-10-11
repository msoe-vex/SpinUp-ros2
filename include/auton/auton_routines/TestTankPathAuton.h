#pragma once

#include "auton/Auton.h"
#include "nodes/subsystems/IDriveNode.h"
#include "nodes/odometry_nodes/OdometryNode.h"
#include "auton/auton_actions/FollowPathAction.h"
#include "pathing/PathManager.h"
#include "pathing/Path.h"
#include "pursuit/path_pursuit/TankPathPursuit.h"
#include "eigen/Eigen/Dense"

class TestTankPathAuton : public Auton {
public:
    TestTankPathAuton(IDriveNode* drive_node, OdometryNode* odom_node);

    void AddNodes();

private:
    IDriveNode* m_drive_node;
    OdometryNode* m_odom_node;
    AutonNode* m_path_node;
    PathManager* m_path_manager;
};