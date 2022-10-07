#pragma once

#include "lib-rr/pursuit/pose_pursuit/IPosePursuit.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "lib-rr/pathing/Path.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/util/PID.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/math/Pose.h"

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