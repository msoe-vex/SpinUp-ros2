#pragma once

#include "api.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "lib-rr/math/Pose.h"

class Waypoint {
private:
    Pose m_position;
    Vector2d m_velocity;
    float m_time;

public:
    Waypoint(Pose position, Vector2d velocity, float time);

    Pose getPosition();

    Vector2d getVelocity();

    float getTime();
};