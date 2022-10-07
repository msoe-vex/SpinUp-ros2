#pragma once

#include "lib-rr/math/Math.h"

class Rotation2d{
protected:
	double m_cos, m_sin;

public:
	Rotation2d();
	Rotation2d(double x, double y, bool doNormalize);
	Rotation2d(const Rotation2d& other);

	static Rotation2d fromRadians(double radians);
	static Rotation2d fromDegrees(double degrees);

	void normalize();

	double getCos();
	double getSin();

	double getRadians();
	double getDegrees();

	Rotation2d rotateBy(Rotation2d other);
	Rotation2d inverse();
	Rotation2d opposite();

	Rotation2d interpolate(Rotation2d other, double x);
};
