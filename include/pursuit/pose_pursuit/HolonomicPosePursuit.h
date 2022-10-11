#pragma once

#include "pursuit/pose_pursuit/IPosePursuit.h"
#include "eigen/Eigen/Dense"
#include "pathing/Path.h"
#include "util/Timer.h"
#include "util/PID.h"
#include "util/Constants.h"
#include "math/Pose.h"

using namespace Eigen;

class HolonomicPosePursuit : public IPosePursuit {
private:
    PID m_x_pid;
    PID m_y_pid;
    PID m_theta_pid;

public:
    HolonomicPosePursuit(Pose target_pose, Timer timer=Timer());

    virtual void startPursuit();

    virtual TargetVelocity getTargetVelocity(Pose current_pose);

    virtual ~HolonomicPosePursuit();
};