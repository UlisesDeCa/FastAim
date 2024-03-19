#include "IOManagement.h"
#include "../Utilities/skCrypter.h"
#include <windows.h>
#include <iostream>
#include <thread>

#pragma comment(lib, "interception.lib")

Interception::Interception() {

	std::cerr << _("[Interception] Starting\n");
	m_Context = interception_create_context();
	interception_set_filter(m_Context, interception_is_mouse, INTERCEPTION_FILTER_MOUSE_MOVE);
	m_Device = interception_wait(m_Context);

	while (interception_receive(m_Context, m_Device = interception_wait(m_Context), &m_Stroke, 1) > 0) {
		if (interception_is_mouse(m_Device))
		{
			InterceptionMouseStroke& mstroke = *(InterceptionMouseStroke*)&m_Stroke;
			interception_send(m_Context, m_Device, &m_Stroke, 1);
			break;
		}
	}

	std::thread normal(&Interception::NormalMouse, this);
	normal.detach();

	std::cerr << _("[Interception] Started\n");
}

void Interception::NormalMouse() {
	while (interception_receive(m_Context, m_Device = interception_wait(m_Context), &m_Stroke, 1) > 0) {
		if (interception_is_mouse(m_Device))
		{
			InterceptionMouseStroke& mstroke = *(InterceptionMouseStroke*)&m_Stroke;
			interception_send(m_Context, m_Device, &m_Stroke, 1);
		}
	}
}

void Interception::Aim(int x, int y) {
	InterceptionMouseStroke& mstroke = *(InterceptionMouseStroke*)&m_Stroke;
	mstroke.flags = INTERCEPTION_MOUSE_MOVE_RELATIVE;
	mstroke.information = 0;
	mstroke.x = x;
	mstroke.y = y;
	interception_send(m_Context, m_Device, &m_Stroke, 1);
}

Interception::~Interception() {
	// Destructor
}