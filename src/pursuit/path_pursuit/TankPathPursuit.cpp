#include "lib-rr/pursuit/path_pursuit/TankPathPursuit.h"

TankPathPursuit::TankPathPursuit(Path path, Timer timer) : IPathPursuit(path, timer),
        m_linear_pid(0.03, 0., 0., 0.),
        m_curve_pid(0.027, 0, 0, 0),
        m_curve_turning_pid(0.27, 0, 0, 0) {
    
}

void TankPathPursuit::startPursuit() {
    m_timer.Start();
}

IPursuit::TargetVelocity TankPathPursuit::getTargetVelocity(Pose current_pose) {
    Pose next_pose = m_path.update(m_timer.Get());

    // Create a vector representing the movement required by the robot, in the robot coordinate frame
    Vector2d robot_error = next_pose.position - current_pose.position;

    //std::cout << "Current: (" << current_pose.position.x() << "," << current_pose.position.y() << ") | Next: (" << next_pose.position.x() << "," << next_pose.position.y() << ")" << std::endl;

    //std::cout << "Current: " << current_pose.angle.angle() << ") | Next: (" << next_pose.angle.angle() << ")" << std::endl;

    // Determine the angle between the positive x-axis and the angle to the new point from the robot's position
    Eigen::Rotation2Dd path_angle = Eigen::Rotation2Dd(atan2(robot_error(1), robot_error(0)));

    //std::cout << "C_X: " << current_pose.position.x() << " | C_Y: " << current_pose.position.y() << " | C_A: " << current_pose.angle.angle() << std::endl;
    //std::cout << "H_A: " << current_pose.angle.angle() << std::endl;
    //std::cout << "N_A: " << next_pose_angle.angle() << endl;

    // Determine the angle between the current pose and the next pose
    // https://www.cuemath.com/geometry/angle-between-vectors/
    // Theta error is positive when the next pose angle is larger than the robot angle
    // Positive when we want to turn left
    float theta_error = (next_pose.angle * current_pose.angle.inverse()).smallestAngle();
    //std::cout << "Current: " << current_pose.angle.angle() << " | Next: " << next_pose_angle.angle() <<  " | Theta: " << theta_error << std::endl;

    // Check if we should be moving in reverse; this happens when the difference between the path angle and the pose
    // angle is greater than 90 degrees (likely around 180 degrees)
    int reverse_path = abs((next_pose.angle * path_angle.inverse()).smallestAngle()) > M_PI_2 ? -1 : 1;

    // Create feedback to give the motors - this is v from the guide below
    float motor_feedback = 0;

    // Create offset to give motors when turning
    float offset = 0;

    // Special case if we are travelling on a straight line
    if (theta_error == 0) {
        std::cout << "Straight Line" << std::endl;
        motor_feedback = m_linear_pid.calculate(robot_error.norm());
    } else {
        // Based on this guide:
        // https://acme-robotics.gitbook.io/road-runner/tour/kinematics

        // Figure out the radius of the curvature
        float curve_radius = (robot_error.norm() / 2) / sin(abs(theta_error));

        // Determine the circumference of the circle
        float circumference = M_PI * 2 * curve_radius;

        // Determine the arc length the robot is travelling on
        float arc_length_to_point = curve_radius * 2 * abs(theta_error);

        // Determine the robot speed based on the arc length
        // In the guide, THIS IS v
        motor_feedback = m_curve_pid.calculate(arc_length_to_point);

        // Determine the drive direction as a positive or negative unit
        // Curving to the left is positive, curving to the right is negative
        int direction = theta_error / abs(theta_error);

        // Determine the angle offset for our motor speeds
        //offset = direction * min(pow(motor_feedback * (DRIVE_TRACK_WIDTH / (2 * curve_radius)) * 0.00001, 0.1), 1.0);
        offset = m_curve_turning_pid.calculate(theta_error);
        //std::cout << "T: " << theta_error << " | CR: " << curve_radius << " | CIR: " << circumference << " | AL: " << arc_length_to_point << " | MF:" << motor_feedback << " | OFF: " << offset << std::endl;
    }

    // Motor speeds will be as follows:
    // Left motor = feedback - offset
    // Right motor = feedback + offset

    // Return the target velocities, and whether the path is at the end point
    IPursuit::TargetVelocity target_velocity = {
        Vector2d(0, motor_feedback * MAX_VELOCITY * reverse_path), 
        offset * MAX_VELOCITY,
        m_path.isComplete()
    };
    
    return target_velocity;
}

TankPathPursuit::~TankPathPursuit() {

}