#include "Vector.h"
Vector::Vector()
{
}
Vector::Vector(float f, float s, float t)
	:x(f), y(s), z(t)
{
}
Vector::Vector(const Vector& obj)
{
	this->x = obj.x;
	this->y = obj.y;
	this->z = obj.z;
}

Vector Vector::operator=(Vector& obj)
{
	this->x = obj.x;
	this->y = obj.y;
	this->z = obj.z;
	return *this;
}
float Vector::getX() { return x; }
float Vector::getY() { return y; }
float Vector::getZ() { return z; }
void Vector::setX(float value) { x = value; }
void Vector::setY(float value) { y = value; }
void Vector::setZ(float value) { z = value; }