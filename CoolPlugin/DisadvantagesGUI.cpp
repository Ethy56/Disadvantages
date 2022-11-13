#include "pch.h"
#include "Disadvantages.h"

void Disadvantages::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

std::string Disadvantages::GetPluginName()
{
	return "Disadvantages";
}

void Disadvantages::RenderSettings() {
	ImGui::TextUnformatted("Disadvantages by Ethy");
	CVarWrapper enableCvar = cvarManager->getCvar("enabled_dis");
	if (!enableCvar) return;
	bool enabled = enableCvar.getBoolValue();
	if (ImGui::Checkbox("Enable plugin", &enabled)) {
		enableCvar.setValue(enabled);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Enable the Disadvantages Plugin");
	}
	if (!enabled) return;
	CVarWrapper playersCvar = cvarManager->getCvar("players_dis");
	if (!playersCvar) return;
	bool players = playersCvar.getBoolValue();

	if (ImGui::Checkbox("Enable player effects", &players)) {
		playersCvar.setValue(players);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Enable Disadvantages to affect players");
	}

	if (players) {
		CVarWrapper fullStopCvar = cvarManager->getCvar("players_fs_dis");
		if (!fullStopCvar) return;

		CVarWrapper invertCvar = cvarManager->getCvar("players_invert_dis");
		if (!invertCvar) return;


		if (ImGui::Button("Enable Players Full Stop")) {
			fullStopCvar.setValue(true);
			invertCvar.setValue(false);
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Enabled will make Disadvantages set the players velocity to 0.");
		}

		if (ImGui::Button("Enable Players Invert")) {
			invertCvar.setValue(true);
			fullStopCvar.setValue(false);
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Enabled will make Disadvantages set the players velocity to whatever is backwards.");
		}

		CVarWrapper blueEnableCvar = cvarManager->getCvar("players_blue_dis");
		if (!blueEnableCvar) return;

		bool bnabled = blueEnableCvar.getBoolValue();
		if (ImGui::Checkbox("Enable Blue Team effects", &bnabled)) {
			blueEnableCvar.setValue(bnabled);
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Enable effects for blue team");
		}

		CVarWrapper orangeEnableCvar = cvarManager->getCvar("players_orange_dis");
		if (!orangeEnableCvar) return;

		bool onabled = orangeEnableCvar.getBoolValue();

		if (ImGui::Checkbox("Enable Orange Team effects", &onabled)) {
			orangeEnableCvar.setValue(onabled);
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Enable effects for orange team");
		}

		CVarWrapper delayCvar = cvarManager->getCvar("players_delay_dis");
		if (!delayCvar) return;

		int delay = delayCvar.getIntValue();
		if (ImGui::SliderInt("Player Delay amount", &delay, 1, 60)) {
			delayCvar.setValue(delay);
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Delay between when players effects are given. Effects will be given after around delay seconds.");
		}
		ImGui::Separator();
	}

	CVarWrapper ballCvar = cvarManager->getCvar("ball_dis");
	if (!ballCvar) return;
	bool ball = ballCvar.getBoolValue();
	if (ImGui::Checkbox("Enable ball effects", &ball)) {
		ballCvar.setValue(ball);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Enable Disadvantages to affect the ball");
	}

	if (ball) {
		CVarWrapper ballfullStopCvar = cvarManager->getCvar("ball_fs_dis");
		if (!ballfullStopCvar) return;

		CVarWrapper ballinvertCvar = cvarManager->getCvar("ball_invert_dis");
		if (!ballinvertCvar) return;

		if (ImGui::Button("Enable Ball Full Stop")) {
			ballfullStopCvar.setValue(true);
			ballinvertCvar.setValue(false);
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Enabled will make Disadvantages set the balls velocity to 0.");
		}

		if (ImGui::Button("Enable Ball Invert")) {
			ballinvertCvar.setValue(true);
			ballfullStopCvar.setValue(false);
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Enabled will make Disadvantages set the balls velocity to whatever is backwards.");
		}

		CVarWrapper balldelayCvar = cvarManager->getCvar("ball_delay_dis");
		if (!balldelayCvar) return;

		int balldelay = balldelayCvar.getIntValue();
		if (ImGui::SliderInt("Ball Delay amount", &balldelay, 1, 60)) {
			balldelayCvar.setValue(balldelay);
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Delay between when ball effects are given. Effects will be given after around delay seconds.");
		}
		ImGui::Separator();
	}
}