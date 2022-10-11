#pragma once

#include "pursuit/path_pursuit/IPathPursuit.h"
#include "pursuit/IPursuit.h"
#include "eigen/Eigen/Dense"
#include "pathing/Path.h"
#include "util/Timer.h"
#include "util/PID.h"
#include "util/Constants.h"
#include "math/Pose.h"
#include "util/Logger.h"

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