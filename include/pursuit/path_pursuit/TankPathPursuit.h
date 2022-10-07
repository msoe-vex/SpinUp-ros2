#pragma once

#include <math.h>
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

class TankPathPursuit : public IPathPursuit {
private:
    PID m_linear_pid;
    PID m_curve_pid;
    PID m_curve_turning_pid;

public:
    TankPathPursuit(Path path, Timer timer=Timer());

    virtual void startPursuit();

    virtual IPursuit::TargetVelocity getTargetVelocity(Pose current_pose);

    virtual ~TankPathPursuit();
};