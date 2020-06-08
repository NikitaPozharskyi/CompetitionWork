#pragma once
#include "Vector.h"
class OutputState
{
public:
	OutputState();
	OutputState(Vector f, char sy);
	OutputState(Vector f, char sy, Vector s);
	OutputState(Vector f, char sy, Vector s, Vector r);
	OutputState(OutputState& obj);
	OutputState operator= (OutputState& obj);
	Vector first;
	char symbol;
	Vector second;
	Vector result;
	float resul;// если результат €вл€етс€ числом, например простые арифметичкские операци€ дают в результате отдельный вектор, который есть выше, а скал€рное произведение и так далее, дают числовой показатель.
};

