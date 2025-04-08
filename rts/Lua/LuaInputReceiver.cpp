/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */


#include <string>

#include "LuaInputReceiver.h"
#include "System/EventHandler.h"

#include <tracy/Tracy.hpp>


CLuaInputReceiver::CLuaInputReceiver()
: CInputReceiver(MANUAL)
{
}


CLuaInputReceiver::~CLuaInputReceiver() = default;


CLuaInputReceiver* CLuaInputReceiver::GetInstance()
{
	RECOIL_DETAILED_TRACY_ZONE;
	static CLuaInputReceiver instance;

	return &instance;
}


bool CLuaInputReceiver::KeyPressed(int keyCode, int scanCode, bool isRepeat)
{
	RECOIL_DETAILED_TRACY_ZONE;
	return eventHandler.KeyPress(keyCode, scanCode, isRepeat);
}


bool CLuaInputReceiver::KeyReleased(int keyCode, int scanCode)
{
	RECOIL_DETAILED_TRACY_ZONE;
	return eventHandler.KeyRelease(keyCode, scanCode);
}


bool CLuaInputReceiver::MousePress(int x, int y, int button)
{
	RECOIL_DETAILED_TRACY_ZONE;
	return eventHandler.MousePress(x, y, button);
}


void CLuaInputReceiver::MouseMove(int x, int y, int dx, int dy, int button)
{
	RECOIL_DETAILED_TRACY_ZONE;
	eventHandler.MouseMove(x, y, dx, dy, button);
}


void CLuaInputReceiver::MouseRelease(int x, int y, int button)
{
	RECOIL_DETAILED_TRACY_ZONE;
	eventHandler.MouseRelease(x, y, button);
}


bool CLuaInputReceiver::IsAbove(int x, int y)
{
	RECOIL_DETAILED_TRACY_ZONE;
	return eventHandler.IsAbove(x, y);
}


std::string CLuaInputReceiver::GetTooltip(int x, int y)
{
	RECOIL_DETAILED_TRACY_ZONE;
	return eventHandler.GetTooltip(x, y);
}


void CLuaInputReceiver::Draw()
{
	RECOIL_DETAILED_TRACY_ZONE;
	return eventHandler.DrawScreen();
}
