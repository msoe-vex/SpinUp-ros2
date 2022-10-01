#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/pursuit/path_pursuit/IPathPursuit.h"
#include "lib-rr/math/Pose.h"
#include "lib-rr/util/Logger.h"

class FollowPathAction : public AutonAction {
private:
    IDriveNode* m_drive_node;
    OdometryNode* m_odom_node;
    IPathPursuit* m_pursuit;
    Path m_path;
    bool m_reset_pose;
    double m_end_dist_threshold;
    Timer m_timer;

public:
    FollowPathAction(IDriveNode* drive_node, OdometryNode* odom_node, IPathPursuit* pursuit, Path path, bool reset_pose=false, double m_end_dist_threshold=16.);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};