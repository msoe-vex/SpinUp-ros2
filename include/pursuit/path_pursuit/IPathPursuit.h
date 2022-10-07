#pragma once

#include "lib-rr/pursuit/IPursuit.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "lib-rr/pathing/Path.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/math/Pose.h"
#include "lib-rr/util/Logger.h"

using namespace Eigen;

class IPathPursuit : public IPursuit {
protected:
    Path m_path;

public:
    IPathPursuit(Path path, Timer timer=Timer()): IPursuit(timer), m_path(path) {};

    virtual void startPursuit() = 0;

    virtual IPursuit::TargetVelocity getTargetVelocity(Pose current_pose) = 0;

    virtual ~IPathPursuit() {};
};