#pragma once

#include "Trans2d.h"

class Position2d{
public:
	struct Delta{
		double dx, dy, dtheta;

		Delta(double x, double y, double t);
	};

protected:
	Trans2d m_translation;
	Rotation2d m_rotation;

public:
	Position2d();
	Position2d(Trans2d tran, Rotation2d rot);
	Position2d(const Position2d& other);

	static Position2d fromTranslation(Trans2d tran);
	static Position2d fromRotation(Rotation2d rot);
	static Position2d fromVelocity(Delta delta);

	Trans2d getTranslation();
	void setTranslation(Trans2d tran);
	Rotation2d getRotation();
	void setRotation(Rotation2d rot);

	Position2d transformBy(Position2d other);

	Position2d inverse();

	Position2d interpolate(Position2d other, double x);


};
