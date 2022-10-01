#pragma once

#include <algorithm>
#include <initializer_list>

#include "lib-rr/kinematics/IDriveKinematics.h"
#include "lib-rr/util/Constants.h"

class HolonomicDriveKinematics : public IDriveKinematics {
public:
    struct HolonomicWheelLocations {
        Vector2d left_front_location;
        Vector2d left_rear_location;
        Vector2d right_front_location;
        Vector2d right_rear_location;
    };

    HolonomicDriveKinematics(EncoderConfig encoder_config, HolonomicWheelLocations wheel_locations, 
        Pose current_pose=Pose());

    /**
     * This function takes in encoder values of all motors, and uses them to update
     * the position of the robot based on the change of position over time
     *  
     * @param encoder_vals struct holding encoder values for all motors
     */
    virtual void updateForwardKinematics(IDriveNode::FourMotorDriveEncoderVals encoder_vals);

    /**
     * This function takes in movements of a drivetrain in the x, y, and theta axes.
     * The inputs of this function must be of the same units (m/s, volts, etc.) and 
     * the function will return the proportion of the supplied maximum to send to each
     * 
     * @param x float representing the x-movement of the drivetrain
     * @param y float representing the y-movement of the drivetrain
     * @param theta float representing the rotational movement of the drivetrain
     * @returns struct containing percentage of the supplied maximum to send to each motor
     */
    virtual FourMotorPercentages inverseKinematics(float x, float y, float theta, float max);

    virtual FourMotorPercentages simpleKinematics(float left_x, float left_y, float right_x, float right_y, float max);

    ~HolonomicDriveKinematics();

private:
    float m_left_front_previous_dist;
    float m_left_rear_previous_dist;
    float m_right_front_previous_dist;
    float m_right_rear_previous_dist;

    HolonomicWheelLocations m_wheel_locations;

};