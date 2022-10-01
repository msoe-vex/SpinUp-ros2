#pragma once

#include "lib-rr/nodes/NodeManager.h"

class IDriveNode : public Node {
public:     
    struct FourMotorDriveEncoderVals {
        int left_front_encoder_val;
        int left_rear_encoder_val;
        int right_front_encoder_val;
        int right_rear_encoder_val;
    };

    IDriveNode(NodeManager* node_manager): Node(node_manager, 10) {};

    virtual void initialize() = 0;

    virtual void resetEncoders() = 0;

    virtual FourMotorDriveEncoderVals getIntegratedEncoderVals() = 0;

    virtual void setDriveVoltage(int y_voltage, int theta_voltage) = 0;

    virtual void setDriveVoltage(int x_voltage, int y_voltage, int theta_voltage) = 0;

    virtual void setDriveVelocity(float y_velocity, float theta_velocity) = 0;

    virtual void setDriveVelocity(float x_velocity, float y_velocity, float theta_velocity) = 0;

    virtual void teleopPeriodic() {};

    virtual void autonPeriodic() {};

    virtual ~IDriveNode() {};
};
