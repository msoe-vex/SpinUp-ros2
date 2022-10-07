#pragma once

#include "Rotation2d.h"

class Trans2d{
protected:
	double m_x, m_y;

public:
	Trans2d();

	Trans2d(double x, double y);

	double norm();

	double getX();

	double getY();

	void setX(double x);

	void setY(double y);

	Trans2d translateBy(Trans2d other);

	Trans2d rotateBy(Rotation2d rotation);

	Trans2d inverse();

	Trans2d interpolate(Trans2d other, double x);

	Trans2d extrapolate(Trans2d other, double x);

	Trans2d flipX();
	Trans2d flipY();

	double getSin();
	double getCos();


};
