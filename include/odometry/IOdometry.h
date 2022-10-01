#pragma once

#include "api.h"
#include "lib-rr/math/Pose.h"
#include "lib-rr/math/Math.h"
#include "lib-rr/util/Encoders.h"
#include "lib-rr/util/Constants.h"

class IOdometry {
public:
    struct EncoderLocations {
        Vector2d x_encoder_location;
        Vector2d y_encoder_location;
    };

    IOdometry(EncoderConfig encoder_1_config, EncoderConfig encoder_2_config, EncoderLocations locations, Pose current_pose=Pose());

    void ResetEncoderTicks(double encoder_1_ticks=0, double encoder_2_ticks=0);

    Pose GetPose();

    void SetCurrentPose(Pose current_pose);

    virtual void Update(double encoder_1_raw_ticks, double encoder_2_raw_ticks, double track_width) {}
    virtual void Update(double encoder_1_raw_ticks, double encoder_2_raw_ticks, Rotation2Dd gyro_angle) = 0;

    ~IOdometry();

protected:
    Rotation2Dd m_gyro_initial_angle;

    Pose m_robot_pose = Pose(Vector2d(0, 0), Rotation2Dd());

    bool m_pose_reset = true;

    double m_encoder_1_ticks_to_dist;
    double m_encoder_2_ticks_to_dist;

    double m_last_encoder_1_dist;
    double m_last_encoder_2_dist;

    Rotation2Dd m_gyro_offset = Rotation2Dd(GYRO_OFFSET);
};