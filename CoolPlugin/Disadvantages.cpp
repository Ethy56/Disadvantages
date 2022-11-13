#include "pch.h"
#include "Disadvantages.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <random>

BAKKESMOD_PLUGIN(Disadvantages, "Disadvantages", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
bool pluginEnabled = false;
bool blueEnabled = false;
bool orangeEnabled = false;

struct Thing {
	bool enabled = false;
	bool invert = false;
	bool fs = true;
	bool bTeam = false;
	bool oTeam = false;
	int delay = 15;
};

Thing ball, players;

//bool fullStop = false;
//bool useInvert = false;
//float intervalVal = 20.0f;

Vector GetCarVelocity(CarWrapper player) {
	if (players.fs) return Vector(0, 0, 0);
	Vector newveloc = player.GetVelocity();
	if (players.invert) {
		newveloc.X *= -1;
		newveloc.Y *= -1;
		newveloc.Z *= -1;
	}
	return newveloc;
};

Vector GetCarAngularVelocity(CarWrapper player) {
	if (players.fs) return Vector(0, 0, 0);
	Vector newveloc = player.GetAngularVelocity();
	if (players.invert) {
		newveloc.X *= -1;
		newveloc.Y *= -1;
		newveloc.Z *= -1;
	}
	return newveloc;
}

Vector GetBallVelocity(BallWrapper thisball) {
	if (ball.fs) return Vector(0, 0, 0);
	Vector newveloc = thisball.GetVelocity();
	if (ball.invert) {
		newveloc.X *= -1;
		newveloc.Y *= -1;
		newveloc.Z *= -1;
	}
	return newveloc;
}

Vector GetBallAngularVelocity(BallWrapper thisball) {
	if (ball.fs) return Vector(0, 0, 0);
	Vector newveloc = thisball.GetAngularVelocity();
	if (ball.invert) {
		newveloc.X *= -1;
		newveloc.Y *= -1;
		newveloc.Z *= -1;
	}
	return newveloc;
}

void Disadvantages::onLoad()
{
	using namespace std::placeholders;
	_globalCvarManager = cvarManager;
	cvarManager->log("Disadvantages Loaded!");

	gameWrapper->HookEvent("Function TAGame.Car_TA.SetVehicleInput", [this](std::string somthing) { tick(); });
	cvarManager->registerCvar("enabled_dis", "0", "Enable Disadvantages", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			pluginEnabled = cvar.getBoolValue();
		});
	cvarManager->registerCvar("players_dis", "0", "Enable player effects", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			players.enabled = cvar.getBoolValue();
		});
	cvarManager->registerCvar("ball_dis", "0", "Enable ball effects", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			ball.enabled = cvar.getBoolValue();
		});
	cvarManager->registerCvar("players_fs_dis", "0", "Enable Players Full Stop", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			players.fs = cvar.getBoolValue();
		});
	cvarManager->registerCvar("players_invert_dis", "0", "Enable Players Invert", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			players.invert = cvar.getBoolValue();
		});
	cvarManager->registerCvar("players_blue_dis", "0", "Enable Blue Team effects", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			players.bTeam = cvar.getBoolValue();
		});
	cvarManager->registerCvar("players_orange_dis", "0", "Enable Orange Team effects", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			players.oTeam = cvar.getBoolValue();
		});
	cvarManager->registerCvar("players_delay_dis", std::to_string(20), "Player Delay amount", true, true, 1, true, 60)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			players.delay = cvar.getIntValue();
		});
	cvarManager->registerCvar("ball_fs_dis", "0", "Enable Players Full Stop", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			ball.fs = cvar.getBoolValue();
		});
	cvarManager->registerCvar("ball_invert_dis", "0", "Enable Players Invert", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			ball.invert = cvar.getBoolValue();
		});
	cvarManager->registerCvar("ball_delay_dis", std::to_string(20), "Ball Delay amount", true, true, 1, true, 60)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			ball.delay = cvar.getIntValue();
		});
}

void Disadvantages::onUnload() {
	cvarManager->log("Disadvantages Unloaded!");
}

void Disadvantages::tick() {
	if (!pluginEnabled) return;
	ServerWrapper server = gameWrapper->GetCurrentGameState();
	if (!server) return;
	auto playlist = server.GetPlaylist();
	if (!playlist) return;
	int playlistId = playlist.GetPlaylistId();
	if (!playlistId) return;
	if (playlistId != 7 && playlistId != 8 && playlistId != 9 && playlistId != 21 && playlistId != 24) return;
	Disadvantages::timeUntilSecond -= 1;
	if (Disadvantages::timeUntilSecond <= 0) {
		updateCount(server);
		Disadvantages::timeUntilSecond = 120;
		if (players.enabled) {
			Disadvantages::playerTime -= 1;
			if (Disadvantages::playerTime <= 0) {
				Disadvantages::playerTime = Disadvantages::count * players.delay;
				updatePlayers(server);
			}
		}
		if (ball.enabled) {
			Disadvantages::ballTime -= 1;
			if (Disadvantages::ballTime <= 0) {
				Disadvantages::ballTime = Disadvantages::count * ball.delay;
				updateBall(server);
			}
		}
	}
}

void Disadvantages::updateCount(ServerWrapper server) {
	auto arr = server.GetPlayers();
	if (arr.IsNull()) {
		Disadvantages::count = 1;
		return;
	};
	Disadvantages::count = arr.Count();
	if (Disadvantages::count < 1) {
		Disadvantages::count = 1;
	}
}

void Disadvantages::updatePlayers(ServerWrapper server) {
	auto teams = server.GetTeams();
	if (teams.IsNull()) { return; }
	TeamWrapper Team1 = teams.Get(0);
	TeamWrapper Team2 = teams.Get(1);
	if (players.bTeam && Team1) {
		auto members = Team1.GetMembers();
		if (members.IsNull()) return;
		int count = members.Count();
		if (count == 1) {
			CarWrapper player = members.Get(0).GetCar();
			if (!player) return;
			Vector veloc = GetCarVelocity(player);
			player.SetVelocity(veloc);
			Vector aveloc = GetCarAngularVelocity(player);
			player.SetAngularVelocity(aveloc, false);
		} else if (count >= 2) {
			int val = 0;
			for (val, count; val != count; ++val) {
				CarWrapper player = members.Get(val).GetCar();
				if (!player) return;
				Vector veloc = GetCarVelocity(player);
				player.SetVelocity(veloc);
				Vector aveloc = GetCarAngularVelocity(player);
				player.SetAngularVelocity(aveloc, false);
			}
		}
	}
	if (players.oTeam && Team2) {
		auto members = Team2.GetMembers();
		if (members.IsNull()) return;
		int count = members.Count();
		if (count == 1) {
			CarWrapper player = members.Get(0).GetCar();
			if (!player) return;
			Vector veloc = GetCarVelocity(player);
			player.SetVelocity(veloc);
			Vector aveloc = GetCarAngularVelocity(player);
			player.SetAngularVelocity(aveloc, false);
		} else if (count >= 2) {
			int val = 0;
			for (val, count; val != count; ++val) {
				CarWrapper player = members.Get(val).GetCar();
				if (!player) return;
				Vector veloc = GetCarVelocity(player);
				player.SetVelocity(veloc);
				Vector aveloc = GetCarAngularVelocity(player);
				player.SetAngularVelocity(aveloc, false);
			}
		}
	}
};

void Disadvantages::updateBall(ServerWrapper server) {
	BallWrapper thisball = server.GetBall();
	Vector veloc = GetBallVelocity(thisball);
	thisball.SetVelocity(veloc);
	Vector aveloc = GetBallAngularVelocity(thisball);
	thisball.SetAngularVelocity(aveloc, false);
}