#pragma once

#include "lib-rr/eigen/Eigen/Dense"

using namespace Eigen;

struct Pose {
    Vector2d position;
    Rotation2Dd angle;

    Pose(Vector2d positionIn, Rotation2Dd angleIn) {
        position = positionIn;
        angle = angleIn;
    }

    Pose() {
        position = Vector2d(0, 0);
        angle = Rotation2Dd(0);
    }

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};