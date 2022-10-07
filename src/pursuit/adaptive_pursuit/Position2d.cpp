#include "lib-rr/pursuit/adaptive_pursuit/Position2d.h"

Position2d::Delta::Delta(double x, double y, double t) {
	dx = x;
	dy = y;
	dtheta = t;
}

Position2d::Position2d() {
	m_translation = Trans2d();
	m_rotation = Rotation2d();
}

Position2d::Position2d(Trans2d tran, Rotation2d rot) {
	m_translation = tran;
	m_rotation = rot;
}

Position2d::Position2d(const Position2d& other) {
	m_translation = other.m_translation;
	m_rotation = other.m_rotation;
}

Position2d Position2d::fromTranslation(Trans2d tran) {
	return Position2d(tran, Rotation2d());
}

Position2d Position2d::fromRotation(Rotation2d rot) {
	return Position2d(Trans2d(), rot);
}

Position2d Position2d::fromVelocity(Delta delta) {
	double sinT = sin(delta.dtheta);
	double cosT = cos(delta.dtheta);
	double s, c;
	if(fabs(delta.dtheta) < kE){
		s = 1.0 - 1.0 / 6.0 * delta.dtheta * delta.dtheta;
		c = .5 * delta.dtheta;
	} else {
		s = sinT / delta.dtheta;
		c = (1.0 - cosT) / delta.dtheta;
	}
	return Position2d(Trans2d(delta.dx * s - delta.dy * c, delta.dx * c + delta.dy * s),
			Rotation2d(cosT, sinT, false));
}

Trans2d Position2d::getTranslation() {
	return m_translation;
}

void Position2d::setTranslation(Trans2d tran) {
	m_translation = tran;
}

Rotation2d Position2d::getRotation() {
	return m_rotation;
}

void Position2d::setRotation(Rotation2d rot) {
	m_rotation = rot;
}

Position2d Position2d::transformBy(Position2d other) {
	return Position2d(m_translation.translateBy(other.m_translation.rotateBy(m_rotation)),
			m_rotation.rotateBy(other.m_rotation));
}

Position2d Position2d::inverse() {
	Rotation2d invert = m_rotation.inverse();
	return Position2d(m_translation.inverse().rotateBy(invert), invert);
}

Position2d Position2d::interpolate(Position2d other, double x) {
	if (x <= 0){
		return *this;
	} else if (x >= 1){
		return other;
	}
	return Position2d(m_translation.interpolate(other.m_translation, x),
			m_rotation.interpolate(other.m_rotation, x));
}
