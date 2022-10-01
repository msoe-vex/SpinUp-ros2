#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/auton/auton_actions/FollowPathAction.h"
#include "lib-rr/pathing/PathManager.h"
#include "lib-rr/pathing/Path.h"
#include "lib-rr/pursuit/path_pursuit/TankPathPursuit.h"
#include "lib-rr/eigen/Eigen/Dense"

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