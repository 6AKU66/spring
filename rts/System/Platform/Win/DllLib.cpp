/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

/**
 * @brief Windows shared library loader implementation
 * Windows Shared Object loader class implementation
 */

#include "DllLib.h"

#include <tracy/Tracy.hpp>

/**
 * Attempts to LoadLibrary on the given DLL
 */
DllLib::DllLib(const char* fileName) : dll(NULL)
{
	//ZoneScoped;
	dll = LoadLibrary(fileName);
}

/**
 * Does a FreeLibrary on the given DLL
 */
void DllLib::Unload() {
	//ZoneScoped;

	FreeLibrary(dll);
	dll = NULL;
}

bool DllLib::LoadFailed() {
	//ZoneScoped;
	return dll == NULL;
}

/**
 * Does a FreeLibrary on the given DLL
 */
DllLib::~DllLib()
{
	//ZoneScoped;
	Unload();
}

/**
 * Attempts to locate the given symbol with GetProcAddress
 */
void* DllLib::FindAddress(const char* symbol)
{
	//ZoneScoped;
	return (void*) GetProcAddress(dll,symbol);
}
