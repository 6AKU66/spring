/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

// #undef NDEBUG

#include "Helper.h"
#include "Registry.h"
#include "SaveLoadUtils.h"

#include <tracy/Tracy.hpp>

void Sim::ClearRegistry() {
	//ZoneScoped;
    Sim::registry.clear();
}

void Sim::LoadComponents(std::stringstream &iss) {
    //ZoneScoped;
    saveLoadUtils.LoadComponents(iss);
}

void Sim::SaveComponents(std::stringstream &oss) {
    //ZoneScoped;
    saveLoadUtils.SaveComponents(oss);
}
