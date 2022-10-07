#include "lib-rr/pathing/PathPoint.h"

PathPoint::PathPoint(float time, Pose pose, Vector2d linear_velocity, float rotational_velocity) {
    m_time = time;
    m_pose = pose;
    m_linear_velocity = linear_velocity;
    m_rotational_velocity = rotational_velocity;
}

float PathPoint::getTime() {
    return m_time;
}

Pose PathPoint::getPose() {
    return m_pose;
}

Vector2d PathPoint::getLinearVelocity() {
    return m_linear_velocity;
}

float PathPoint::getRotationalVelocity() {
    return m_rotational_velocity;
}

PathPoint PathPoint::interpolateTo(PathPoint other, float time) {
    float t = time - getTime();
    float deltaTime = other.getTime() - getTime();

    Eigen::Vector2d acceleration = deltaTime == 0. ? Eigen::Vector2d(0., 0.) : ((other.getLinearVelocity() - getLinearVelocity()) / deltaTime);
    Eigen::Vector2d position = 0.5 * acceleration * (t * t) + getLinearVelocity() * t + getPose().position;
    Eigen::Vector2d velocity = acceleration * t + getLinearVelocity();

    // Logger::logInfo("Time: " + std::to_string(time) + " | position: " + std::to_string(position.x()) + " " + std::to_string(position.y()) + 
    //     " | velocity: " + std::to_string(velocity.x()) + " " + std::to_string(velocity.y()));

    float alpha = deltaTime == 0. ? 0. : (other.getRotationalVelocity() - getRotationalVelocity()) / deltaTime;
    Eigen::Rotation2Dd theta = Eigen::Rotation2Dd(0.5 * alpha * (t * t) + getRotationalVelocity() * t) * getPose().angle;
    float omega = alpha * t + getRotationalVelocity();

    return PathPoint(time, Pose(position, theta), velocity, omega);
}

// Not robust, used for testing
bool PathPoint::equals(PathPoint* other_point) {
    if (other_point == nullptr) {
        return false;
    } else if(this == other_point) {
        return true;
    } else {
        return this->m_time == other_point->m_time && 
            this->m_pose.position == other_point->m_pose.position && 
            this->m_pose.angle.angle() == other_point->m_pose.angle.angle() && 
            this->m_linear_velocity == other_point->m_linear_velocity && 
            this->m_rotational_velocity == other_point->m_rotational_velocity;
    }
}