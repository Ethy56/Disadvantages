#include "pch.h"
#include "Disadvantages.h"
#include <iostream>
#include <vector>
#include <tuple>

BAKKESMOD_PLUGIN(Disadvantages, "Disadvantages", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
bool pluginEnabled = false;
bool blueEnabled = false;
bool orangeEnabled = false;
float intervalVal = 20.0f;

void Disadvantages::onLoad()
{
	using namespace std::placeholders;
	_globalCvarManager = cvarManager;
	Netcode = std::make_shared<NetcodeManager>(cvarManager, gameWrapper, exports,
		std::bind(&Disadvantages::onNetMessage, this, _1, _2));
	cvarManager->log("Disadvantages Loaded!");

	gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](std::string somthing) { tick(); });

	cvarManager->registerCvar("isenabled_dis", "0", "Enable Disadvantages", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		pluginEnabled = cvar.getBoolValue();
			});
	cvarManager->registerCvar("blueenabled_dis", "0", "Enable Disadvantages for Blue", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		blueEnabled = cvar.getBoolValue();
			});
	cvarManager->registerCvar("orangeeenabled_dis", "0", "Enable Disadvantages", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		orangeEnabled = cvar.getBoolValue();
			});
	cvarManager->registerCvar("interval_dis", std::to_string(intervalVal), "Interval of Disadvantage", true, true, 5.0f, true, 100.0f)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		intervalVal = cvar.getFloatValue();
			});
}

void Disadvantages::onUnload() {
	cvarManager->log("Disadvantages Unloaded!");
}

void Disadvantages::tick() {
	CVarWrapper enableCvar = cvarManager->getCvar("isenabled_dis");
	Disadvantages::timeUntilRotate -= 1;
	if (Disadvantages::timeUntilRotate <= 0 && pluginEnabled) {
		Disadvantages::timeUntilRotate = 120 * intervalVal;
		ServerWrapper server = gameWrapper->GetCurrentGameState();
		if (!server) { return; }
		ArrayWrapper teams = server.GetTeams();
		if (teams.IsNull()) { return; }
		TeamWrapper Team1 = teams.Get(0);
		TeamWrapper Team2 = teams.Get(1);
		if (blueEnabled) {
			int count = Team1.GetMembers().Count();
			if (count == 1) {
				CarWrapper player = Team1.GetMembers().Get(0).GetCar();
				player.SetVelocity(Vector(0, 0, 0));
			}
			else if (count >= 2) {
				int val = 0;
				for (val, count; val != count; ++val) {
					CarWrapper player = Team1.GetMembers().Get(val).GetCar();
					player.SetVelocity(Vector(0, 0, 0));
				}
			}
		}
		if (orangeEnabled) {
			int count = Team2.GetMembers().Count();
			if (count == 1) {
				CarWrapper player = Team2.GetMembers().Get(0).GetCar();
				player.SetVelocity(Vector(0, 0, 0));
			}
			else if (count >= 2) {
				int val = 0;
				for (val, count; val != count; ++val) {
					CarWrapper player = Team2.GetMembers().Get(val).GetCar();
					player.SetVelocity(Vector(0, 0, 0));
				}
			}
			cvarManager->log("Stopped Orange");
		}
	}
}

void Disadvantages::onNetMessage(const std::string& Message, PriWrapper Sender) {
	if (Sender.IsNull())
	{
		return;
	}
}