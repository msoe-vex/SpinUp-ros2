#include "lib-rr/pursuit/adaptive_pursuit/Trans2d.h"

Trans2d::Trans2d() {
	m_x = 0;
	m_y = 0;
}

Trans2d::Trans2d(double x, double y) {
	m_x = x;
	m_y = y;
}

double Trans2d::norm() {
	return hypot(m_x, m_y);
}

double Trans2d::getX() {
	return m_x;
}

double Trans2d::getY() {
	return m_y;
}

void Trans2d::setX(double x) {
	m_x = x;
}

void Trans2d::setY(double y) {
	m_y = y;
}

Trans2d Trans2d::translateBy(Trans2d other) {
	return Trans2d(m_x + other.getX(), m_y + other.getY());
}

Trans2d Trans2d::rotateBy(Rotation2d rotation) {
	return Trans2d(m_x * rotation.getCos() - m_y * rotation.getSin(),
			m_x * rotation.getSin() + m_y * rotation.getCos());
}

Trans2d Trans2d::inverse() {
	return Trans2d(-m_x, -m_y);
}

Trans2d Trans2d::interpolate(Trans2d other, double x) {
	if(x <=0){
		return *this;
	} else if (x >= 1){
		return other;
	}
	return extrapolate(other, x);
}

Trans2d Trans2d::extrapolate(Trans2d other, double x) {
	return Trans2d(x * (other.getX() - m_x) + m_x, x * (other.getY() - m_y) + m_y);
}

Trans2d Trans2d::flipX() {
	return Trans2d(-m_x, m_y);
}

Trans2d Trans2d::flipY() {
	return Trans2d(m_x, -m_y);
}

double Trans2d::getSin() {
    return getY() / norm();
}

double Trans2d::getCos() {
    return getX() / norm();
}
