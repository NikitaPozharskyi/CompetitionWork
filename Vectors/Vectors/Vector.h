#pragma once
#include <fstream>
class Vector
{
private:
	float x;
	float y;
	float z;
public:
	Vector();
	Vector(float f, float s, float t);
	Vector(const Vector& obj);
	
	Vector operator=(Vector& obj);
	float getX();
	float getY();
	float getZ();
	void setX(float value);
	void setY(float value);
	void setZ(float value);
	
};

