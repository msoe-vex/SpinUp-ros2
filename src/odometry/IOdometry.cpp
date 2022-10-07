#include "lib-rr/odometry/IOdometry.h"

IOdometry::IOdometry(EncoderConfig encoder_1_config, EncoderConfig encoder_2_config, EncoderLocations locations, Pose current_pose): 
        m_encoder_1_ticks_to_dist((encoder_1_config.wheel_diameter * PI) / 
            encoder_1_config.ticks_per_wheel_revolution),
        m_encoder_2_ticks_to_dist((encoder_2_config.wheel_diameter * PI) / 
            encoder_2_config.ticks_per_wheel_revolution),
        m_last_encoder_1_dist(0),
        m_last_encoder_2_dist(0) {
    SetCurrentPose(current_pose);
}

void IOdometry::ResetEncoderTicks(double encoder_1_ticks, double encoder_2_ticks) {
    m_last_encoder_1_dist = encoder_1_ticks * m_encoder_1_ticks_to_dist;
    m_last_encoder_2_dist = encoder_2_ticks * m_encoder_2_ticks_to_dist;
}

Pose IOdometry::GetPose(){
    return m_robot_pose;
}

void IOdometry::SetCurrentPose(Pose current_pose) {
    m_robot_pose = current_pose;
    m_gyro_offset = current_pose.angle;
    m_pose_reset = true;
}

IOdometry::~IOdometry() {

}

