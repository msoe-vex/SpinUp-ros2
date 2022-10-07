#include "lib-rr/odometry/TankOdometry.h"

TankOdometry::TankOdometry(EncoderConfig leftEncoderConfig, EncoderConfig rightEncoderConfig, EncoderLocations locations,
    Pose currentPose): IOdometry(leftEncoderConfig, rightEncoderConfig, locations, currentPose), m_locations(locations) {

}

/**
 * This function is used to update the internal calculated position of the robot. Not as accurate as gyro version
 *
 * To maximize accuracy in robot position estimation, this function should be called as frequently as possible, ideally
 * at a rate of 50 Hz or greater.
 *
 * @param left_encoder_raw_ticks The distance in ticks measured by the left encoder since when the tracker was last run
 * @param right_encoder_raw_ticks The distance in ticks measured by the right encoder since when the tracker was last run
 * @param track_width The distance between the two sides/tracks of the drivetrain
 */
void TankOdometry::Update(double left_encoder_raw_ticks, double right_encoder_raw_ticks, double track_width) {
    double left_dist = left_encoder_raw_ticks * IOdometry::m_encoder_1_ticks_to_dist;
    double right_dist = right_encoder_raw_ticks * IOdometry::m_encoder_2_ticks_to_dist;

    if (m_pose_reset) {
        IOdometry::m_last_encoder_1_dist = left_dist;
        IOdometry::m_last_encoder_2_dist = right_dist;
        IOdometry::m_pose_reset = false;
    }

    double left_delta = left_dist - IOdometry::m_last_encoder_1_dist;
    double right_delta = right_dist - IOdometry:: m_last_encoder_2_dist;
    double distance_moved = (left_delta + right_delta) / 2.0;

    double rotation = (right_delta - left_delta) / track_width;

    Vector2d robot_translation(0, distance_moved);

    IOdometry::m_robot_pose.angle = IOdometry::m_robot_pose.angle * Rotation2Dd(rotation);
    robot_translation = IOdometry::m_robot_pose.angle * robot_translation;
    IOdometry::m_robot_pose.position += robot_translation;

    IOdometry::m_last_encoder_1_dist = left_dist;
    IOdometry::m_last_encoder_2_dist = right_dist;
}

/**
 * This function is used to update the internal calculated position of the robot
 *
 * To maximize accuracy in robot position estimation, this function should be called as frequently as possible, ideally
 * at a rate of 50 Hz or greater.
 *
 * @param left_encoder_raw_ticks The distance in ticks measured by the left encoder since when the tracker was last run
 * @param right_encoder_raw_ticks The distance in ticks measured by the right encoder since when the tracker was last run
 * @param gyro_angle The current yaw of the robot as measured by the gyro
 */
void TankOdometry::Update(double left_encoder_raw_ticks, double right_encoder_raw_ticks, Rotation2Dd gyro_angle) {
    double left_dist = left_encoder_raw_ticks * IOdometry::m_encoder_1_ticks_to_dist;
    double right_dist = right_encoder_raw_ticks * IOdometry::m_encoder_2_ticks_to_dist;

    if (m_pose_reset) {
        IOdometry::m_last_encoder_1_dist = left_dist;
        IOdometry::m_last_encoder_2_dist = right_dist;
        IOdometry::m_gyro_initial_angle = gyro_angle;
        IOdometry::m_pose_reset = false;
    }

    double left_delta = left_dist - IOdometry::m_last_encoder_1_dist;
    double right_delta = right_dist - IOdometry::m_last_encoder_2_dist;
    double distance_moved = (left_delta + right_delta) / 2.0;

    Vector2d robot_translation(0, distance_moved);
    robot_translation = gyro_angle * robot_translation;
    IOdometry::m_robot_pose.position += robot_translation;

    Eigen::Rotation2Dd angle_offset(M_PI_2);
    IOdometry::m_robot_pose.angle = gyro_angle * IOdometry::m_gyro_initial_angle.inverse() * angle_offset;

    IOdometry::m_last_encoder_1_dist = left_dist;
    IOdometry::m_last_encoder_2_dist = right_dist;
}