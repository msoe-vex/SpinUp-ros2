#include "lib-rr/pathing/Waypoint.h"

Waypoint::Waypoint(Pose position, Vector2d velocity, float time) {
    m_position = position;
    m_velocity = velocity;
    m_time = time;
}

Pose Waypoint::getPosition() {
    return m_position;
}

Vector2d Waypoint::getVelocity() {
    return m_velocity;
}

float Waypoint::getTime() {
    return m_time;
}