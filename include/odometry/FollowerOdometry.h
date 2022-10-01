#pragma once

#include <math.h>
#include "lib-rr/odometry/IOdometry.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/util/Logger.h"

class FollowerOdometry : public IOdometry {
private:
    EncoderLocations m_locations;
    bool m_previously_positive = true;

public:
    FollowerOdometry(EncoderConfig x_encoder_config, EncoderConfig y_encoder_config, EncoderLocations locations, Pose current_pose=Pose());
    
    void Update(double x_encoder_raw_ticks, double y_encoder_raw_ticks, Rotation2Dd gyro_angle);

    ~FollowerOdometry();
};