#pragma once

#include <math.h>
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