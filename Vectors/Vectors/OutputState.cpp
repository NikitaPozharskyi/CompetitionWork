#include "OutputState.h"

OutputState::OutputState()
{
}

OutputState::OutputState(Vector f, char sy)
	:first(f), symbol(sy)
{
}

OutputState::OutputState(Vector f, char sy, Vector s)
	:first(f), symbol(sy), second(s)
{
}

OutputState::OutputState(Vector f, char sy, Vector s, Vector r)
	:first (f), symbol(sy), second(s), result(r)
{
}

OutputState::OutputState(OutputState& obj)
{
	this->first = obj.first;
	this->second = obj.second;
	this->symbol = obj.symbol;
	this->result = obj.result;
}

OutputState OutputState::operator=(OutputState& obj)
{
	this->first = obj.first;
	this->second = obj.second;
	this->symbol = obj.symbol;
	this->result = obj.result;
	return *this;
}
