#include "lib-rr/auton/auton_actions/DriveStraightAction.h"

DriveStraightAction::DriveStraightAction(IDriveNode* drive_node, OdometryNode* odometry_node, DriveStraightParams params, double distance, double max_velocity, double max_accel, double slowDownCoef) :
        m_drive_node(drive_node), 
        m_odometry_node(odometry_node),
        m_params(params),
        m_theta_error_PID(0.35, 0, 0),
        m_distance(distance), // in inches
        m_max_velocity(max_velocity), 
        m_max_accel(max_accel),
        m_slowDownCoef(slowDownCoef) {

}

double DriveStraightAction::m_getUnboundedInstantaneousVelocity(double dt, double lastVelocity) {
    return (m_max_accel * dt) + lastVelocity;
}

void DriveStraightAction::ActionInit() {
    m_lastSpeed = 0.;
    m_lastTime = 0.;
    m_feedForward = 0.;

    m_timer.Start();
    m_drive_node->resetEncoders();
    m_starting_pose = m_odometry_node->getCurrentPose();

    // Calculate how long we take to accelerate to max speed
    double accelerationTimeSec = m_max_velocity / m_max_accel;

    // Determine how long it takes to accelerate (triangle formula)
    m_accelerationDistanceIn = 0.5 * accelerationTimeSec * m_max_velocity;
}

AutonAction::actionStatus DriveStraightAction::Action() {
    // Determine the change in time since the last run
    double dt = m_timer.Get() - m_lastTime;

    // Determine the current pose
    Pose m_current_pose = m_odometry_node->getCurrentPose(); 

    // Determine the current theta error (angle we need to turn)
    double theta_error = (m_current_pose.angle * m_starting_pose.angle.inverse()).smallestAngle();

    // Determine the distance we have already driven in encoder ticks
    double currentDistanceTicks = (m_drive_node->getIntegratedEncoderVals().left_front_encoder_val + m_drive_node->getIntegratedEncoderVals().right_front_encoder_val) / 2.;

    // Determine the distance we have already driven in inches
    double currentDistanceIn = (currentDistanceTicks / m_params.encoderTicksPerRev) * m_params.gearRatio * m_params.wheelCircumference;

    // Determine the remaining distance to drive
    double remainingDistanceIn = max(fabs(m_distance) - fabs(currentDistanceIn), 0.);

    // Start calculating the robot speed (positive val)
    double speed = min(m_getUnboundedInstantaneousVelocity(dt, m_lastSpeed), m_max_velocity);

    // Limit speed if within the deceleration curve
    // Allow the robot twice as long to stop, to account for momentum
    if (remainingDistanceIn < m_accelerationDistanceIn * m_slowDownCoef) {
        // Determine the maximum deceleration speed based on the remaining distance to the target
        double maxDecelerationSpeed = sqrt(remainingDistanceIn * m_max_accel);

        // Set the speed to the minimum of the current speed, and the max curve
        speed = min(speed, maxDecelerationSpeed);
    }

    // Make sure that we never go slower than the feed forward speed
    speed = max(speed, m_feedForward);

    // Determine the turning offset
    double offset = m_theta_error_PID.calculate(theta_error) * speed;    

    // Determine the left and right speeds
    double leftSpeed = speed + offset;
    double rightSpeed = speed - offset;

    // Update the previous values
    m_lastSpeed = speed;
    m_lastTime = m_timer.Get();

    // Return the velocity to the robot
    if (remainingDistanceIn <= 0) {
        return END;
    } else {
        if (m_distance > 0) {
            // m_drive_node->setDriveVelocity(speed, offset);
            m_drive_node->setDriveVelocity(speed, -offset);
        } else {
            m_drive_node->setDriveVelocity(-speed, offset);
        }
        
        return CONTINUE;
    }
}

void DriveStraightAction::ActionEnd() {
    m_drive_node->setDriveVelocity(0, 0);
}