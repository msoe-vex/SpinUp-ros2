#pragma once

#include "eigen/Eigen/Dense"
#include "math/Pose.h"
#include <vector>

class PathPoint {
public:
    PathPoint(float time, Pose pose, Vector2d linear_velocity, float rotational_velocity);
    
    PathPoint(float time, Pose pose, Vector2d linear_velocity, float rotational_velocity, std::vector<std::string> auton_action_names);

    float getTime();

    Pose getPose();

    Vector2d getLinearVelocity();

    float getRotationalVelocity();
    
    std::vector<std::string> getAutonActionNames();

    PathPoint interpolateTo(PathPoint other, float time);

    bool equals(PathPoint* that);
    
private:
    Pose m_pose;
    float m_time;
    Vector2d m_linear_velocity;
    float m_rotational_velocity;
    std::vector<std::string> m_auton_action_names;
};