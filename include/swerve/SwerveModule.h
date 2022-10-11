#pragma once

#include "eigen/Eigen/Dense"
#include "eigen/Eigen/Geometry"
#include "util/Constants.h"

struct MotorPowers {
    int8_t left_motor_power;
    int8_t right_motor_power;
};

class SwerveModule {
private:
    Eigen::Vector2d m_module_location; 
    double m_percent_error;
    double m_total_error;
    double kP;
    double kI;
    double kD;


public:
    SwerveModule (Eigen::Vector2d module_location, double kP, double kI, double kD);

    MotorPowers InverseKinematics(Eigen::Vector2d target_velocity, double target_rotation_velocity, Eigen::Rotation2Dd module_actual_angle);
};