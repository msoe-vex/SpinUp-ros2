#pragma once

#include "lib-rr/pursuit/path_pursuit/IPathPursuit.h"
#include "lib-rr/pursuit/IPursuit.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "lib-rr/pathing/Path.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/util/PID.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/math/Pose.h"
#include "lib-rr/util/Logger.h"

using namespace Eigen;

class HolonomicPathPursuit : public IPathPursuit {
private:
    PID m_x_pid;
    PID m_y_pid;
    PID m_theta_pid;

public:
    HolonomicPathPursuit(Path path, Timer timer=Timer());

    virtual void startPursuit();

    virtual IPursuit::TargetVelocity getTargetVelocity(Pose current_pose);

    virtual ~HolonomicPathPursuit();
};