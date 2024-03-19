#pragma once
#include "../Utilities/interception.h"

class Interception
{
public:
	Interception();

	void Aim(int x, int y);

	~Interception();

private:
	void NormalMouse();

	InterceptionContext m_Context;
	InterceptionDevice m_Device;
	InterceptionStroke m_Stroke;
};