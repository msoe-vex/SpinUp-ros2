#pragma once

#include "lib-rr/pursuit/IPursuit.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "lib-rr/util/Timer.h"
#include "lib-rr/math/Pose.h"
#include "lib-rr/util/Logger.h"

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