#pragma once

#include "pursuit/IPursuit.h"
#include "eigen/Eigen/Dense"
#include "util/Timer.h"
#include "math/Pose.h"
#include "util/Logger.h"

using namespace Eigen;

class IPosePursuit : public IPursuit {
protected:
    Pose m_pose;

public:
    IPosePursuit(Pose pose, Timer timer=Timer()): IPursuit(timer), m_pose(pose) {};

    virtual void startPursuit() = 0;

    virtual IPursuit::TargetVelocity getTargetVelocity(Pose current_pose) = 0;

    virtual ~IPosePursuit() {};
};