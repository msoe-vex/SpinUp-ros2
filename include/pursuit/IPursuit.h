#pragma once

#include "lib-rr/eigen/Eigen/Dense"
#include "lib-rr/util/Timer.h"
#include "lib-rr/math/Pose.h"
#include "lib-rr/util/Logger.h"

using namespace Eigen;

class IPursuit {
protected:
    Timer m_timer;

public:
    struct TargetVelocity {
        Vector2d linear_velocity;
        float rotational_velocity;
        bool is_within_end_tolerance;
    };

    IPursuit(Timer timer=Timer()): m_timer(timer) {};

    virtual void startPursuit() = 0;

    virtual TargetVelocity getTargetVelocity(Pose current_pose) = 0;

    virtual ~IPursuit() {};
};