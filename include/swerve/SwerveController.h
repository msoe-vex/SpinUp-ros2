#pragma once

#include "SwerveModule.h"
#include "lib-rr/eigen/Eigen/Dense"

class SwerveController{
    private:
    Eigen::Rotation2Dd left_actual_angle;
    Eigen::Rotation2Dd right_actual_angle;
    Eigen::Rotation2Dd rear_actual_angle;

    SwerveModule leftSwerveModule;
    SwerveModule rightSwerveModule;
    SwerveModule rearSwerveModule;

    MotorPowers left_motor_powers;
    MotorPowers right_motor_powers;
    MotorPowers rear_motor_powers;

public:
    SwerveController(Eigen::Vector2d left_module_location, Eigen::Vector2d right_module_location,
                     Eigen::Vector2d rear_module_location, double kP, double kI, double kD);
     
    void assignActualAngle(int left_pot, int right_pot, int rear_pot);

    MotorPowers calculateLeftModule(Eigen::Vector2d target_velocity, double rotation_velocity);

    MotorPowers calculateRightModule(Eigen::Vector2d target_velocity, double rotation_velocity);

    MotorPowers calculateRearModule(Eigen::Vector2d target_velocity, double rotation_velocity);
};