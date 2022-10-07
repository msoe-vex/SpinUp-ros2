#include "lib-rr/kinematics/IDriveKinematics.h"

IDriveKinematics::IDriveKinematics(EncoderConfig encoder_config, Pose current_pose) :
        m_ticks_to_distance_m((encoder_config.wheel_diameter * M_PI) / 
            encoder_config.ticks_per_wheel_revolution) {
        setCurrentPose(current_pose);
}

void IDriveKinematics::m_updateCurrentPosition(Vector2d robot_velocity, float theta_velocity, float delta_time) {
    // Multiply position and theta velocity by time to get position
    Vector2d delta_position = robot_velocity * delta_time;
    Rotation2Dd delta_theta(theta_velocity * delta_time);

    // Rotate the translation vector by the current angle rotation matrix
    Vector2d robot_translation = delta_theta * delta_position;

    // Add the current translation onto the robot position vector
    m_pose.position += robot_translation;

    // Rotate the stored robot angle by the delta angle
    m_pose.angle = m_pose.angle * delta_theta;
}

Pose IDriveKinematics::getPose() {
    return m_pose;
}

void IDriveKinematics::setCurrentPose(Pose current_pose) {
    m_pose = current_pose;
}

IDriveKinematics::~IDriveKinematics() {

}