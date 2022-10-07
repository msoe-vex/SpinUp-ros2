#include "lib-rr/kinematics/HolonomicDriveKinematics.h"

HolonomicDriveKinematics::HolonomicDriveKinematics(EncoderConfig encoder_config, HolonomicWheelLocations wheel_locations, 
    Pose current_pose) : IDriveKinematics(encoder_config, current_pose),
        m_wheel_locations(wheel_locations) {

}

void HolonomicDriveKinematics::updateForwardKinematics(IDriveNode::FourMotorDriveEncoderVals encoder_vals) {
    float left_front_dist = encoder_vals.left_front_encoder_val * m_ticks_to_distance_m;
    float left_rear_dist = encoder_vals.left_rear_encoder_val * m_ticks_to_distance_m;
    float right_front_dist = encoder_vals.right_front_encoder_val * m_ticks_to_distance_m;
    float right_rear_dist = encoder_vals.right_rear_encoder_val * m_ticks_to_distance_m;

    float delta_time = m_timer.Get();

    if (m_pose_reset) {
        m_left_front_previous_dist = left_front_dist;
        m_left_rear_previous_dist = left_rear_dist;
        m_right_front_previous_dist = right_front_dist;
        m_right_rear_previous_dist = right_rear_dist;
        m_pose_reset = false;
    }

    // Use a vector to describe the velocity of each wheel
    Vector2d left_front_velocity((left_front_dist - m_left_front_previous_dist) / delta_time, 0);
    Vector2d left_rear_velocity((left_rear_dist - m_left_front_previous_dist) / delta_time, 0);
    Vector2d right_front_velocity((right_front_dist - m_left_front_previous_dist) / delta_time, 0);
    Vector2d right_rear_velocity((right_rear_dist - m_left_front_previous_dist) / delta_time, 0);
    
    // Rotate each of the vectors to their respective orientations
    left_front_velocity = Rotation2Dd(-3 * M_PI_4) * left_front_velocity;
    left_rear_velocity = Rotation2Dd(-1 * M_PI_4) * left_rear_velocity;
    right_front_velocity = Rotation2Dd(3 * M_PI_4) * right_front_velocity;
    right_rear_velocity = Rotation2Dd(M_PI_4) * right_rear_velocity;

    // Calculate the robot translation as the average of all component vectors
    Vector2d robot_velocity = (left_front_velocity + left_rear_velocity + 
                                  right_front_velocity + right_rear_velocity) / 4;

    float theta_velocity = (left_front_velocity.norm() / m_wheel_locations.left_front_location.norm()) + 
                           (left_rear_velocity.norm() / m_wheel_locations.left_rear_location.norm()) + 
                           (right_front_velocity.norm() / m_wheel_locations.right_front_location.norm()) +
                           (right_rear_velocity.norm() / m_wheel_locations.right_rear_location.norm());


    // Send the values to be integrated, to update our current robot position
    IDriveKinematics::m_updateCurrentPosition(robot_velocity, theta_velocity, delta_time);

    // Update the previous values of each encoder
    m_left_front_previous_dist = left_front_dist;
    m_left_rear_previous_dist = left_rear_dist;
    m_right_front_previous_dist = right_front_dist;
    m_right_rear_previous_dist = right_rear_dist;

    // Restart the timer
    m_timer.Start();
}

IDriveKinematics::FourMotorPercentages HolonomicDriveKinematics::inverseKinematics(
        float x, float y, float theta, float max) {
    float front_left = y + x - theta;
    float back_left = y - x - theta;
    float front_right = y - x + theta;
    float back_right = y + x + theta;

    float max_val = std::max({fabs(front_left), fabs(back_left), fabs(front_right), fabs(back_right), max});

    FourMotorPercentages motor_percentages {
        front_left / max_val,
        back_left / max_val,
        front_right / max_val,
        back_right / max_val
    };

    return motor_percentages;
}

IDriveKinematics::FourMotorPercentages HolonomicDriveKinematics::simpleKinematics(
        float left_x, float left_y, float right_x, float right_y, float max) {
    float front_left = left_x + left_y;
    float back_left = -left_x + left_y;
    float front_right = -right_x + right_y;
    float back_right = right_x + right_y;

    float max_val = std::max({fabs(front_left), fabs(back_left), fabs(front_right), fabs(back_right), max});

    FourMotorPercentages motor_percentages {
        front_left / max_val,
        back_left / max_val,
        front_right / max_val,
        back_right / max_val
    };

    return motor_percentages;
}

HolonomicDriveKinematics::~HolonomicDriveKinematics() {

}
