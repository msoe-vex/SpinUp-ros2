#include "lib-rr/odometry/FollowerOdometry.h"

FollowerOdometry::FollowerOdometry(EncoderConfig xEncoderConfig, EncoderConfig yEncoderConfig, EncoderLocations locations,
    Pose currentPose): IOdometry(xEncoderConfig, yEncoderConfig, locations, currentPose), m_locations(locations) {

}

/**
 * This function is used to update the internal calculated position of the robot
 *
 * To maximize accuracy in robot position estimation, this function should be called as frequently as possible, ideally
 * at a rate of 50 Hz or greater.
 *
 * @param x_encoder_raw_ticks The distance in ticks measured by the X encoder since when the tracker was last run
 * @param y_encoder_raw_ticks The distance in ticks measured by the Y encoder since when the tracker was last run
 * @param gyro_angle The current yaw of the robot as measured by the gyro
 */
void FollowerOdometry::Update(double x_encoder_raw_ticks, double y_encoder_raw_ticks, Rotation2Dd gyro_angle) {
    // Convert the current position in ticks to a position in distance units
    double x_encoder_dist = x_encoder_raw_ticks * IOdometry::m_encoder_1_ticks_to_dist;
    double y_encoder_dist = y_encoder_raw_ticks * IOdometry::m_encoder_2_ticks_to_dist;

    // Reset the current position of the robot
    if (m_pose_reset) {
        IOdometry::m_last_encoder_1_dist = x_encoder_dist;
        IOdometry::m_last_encoder_2_dist = y_encoder_dist;
        IOdometry::m_gyro_initial_angle = gyro_angle;
        IOdometry::m_pose_reset = false;
    }

    // Calculate the change in position of each encoder since the last check
    double x_encoder_delta = x_encoder_dist - IOdometry::m_last_encoder_1_dist;
    double y_encoder_delta = y_encoder_dist - IOdometry::m_last_encoder_2_dist;
    Rotation2Dd angle_delta = (gyro_angle * IOdometry::m_gyro_initial_angle.inverse()) 
        * IOdometry::m_gyro_offset * IOdometry::m_robot_pose.angle.inverse(); // Find change in angle

    // Determine the arc length of the turn from the center of each encoder
    double x_arc_length = m_locations.x_encoder_location.norm() * angle_delta.smallestAngle();
    double y_arc_length = m_locations.y_encoder_location.norm() * angle_delta.smallestAngle();

    // Determine the tangential component of each encoder relative to the circle of rotation
    // TODO update to a vector projection
    double x_position_coef = fabs(sin(atan2(m_locations.x_encoder_location.y(), m_locations.x_encoder_location.x())));
    double y_position_coef = fabs(cos(atan2(m_locations.y_encoder_location.y(), m_locations.y_encoder_location.x())));

    // Translate to encoder value
    double x_encoder_turning_component = x_arc_length * x_position_coef;
    double y_encoder_turning_component = y_arc_length * y_position_coef * -1;

    // Calculate the true encoder delta when factoring in contributions from turning
    double x_delta = x_encoder_delta - x_encoder_turning_component;
    double y_delta = y_encoder_delta - y_encoder_turning_component;

    // Convert the x and y deltas into a translation vector
    Vector2d robot_translation(x_delta, y_delta);

    // Update the current angle of the robot position
    // Find the difference of the current angle to the initial angle
    // Rotate this difference by the M_PI_2 offset to put it back in the correct frame of reference
    IOdometry::m_robot_pose.angle = gyro_angle * IOdometry::m_gyro_initial_angle.inverse() * IOdometry::m_gyro_offset;

    // Rotate the translation vector by the current angle rotation matrix
    // We need to rotate this back, as our encoders are oriented with 0 being forward
    robot_translation = (IOdometry::m_robot_pose.angle.inverse() * Rotation2Dd(M_PI_2)).inverse() * robot_translation;

    // Add the current translation onto the robot position vector
    IOdometry::m_robot_pose.position += robot_translation;

    // Update the previous values of the encoders for the next iteration
    IOdometry::m_last_encoder_1_dist = x_encoder_dist;
    IOdometry::m_last_encoder_2_dist = y_encoder_dist;
}