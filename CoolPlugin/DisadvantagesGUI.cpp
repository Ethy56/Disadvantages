#include "pch.h"
#include "Disadvantages.h"

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void Disadvantages::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}


// Name of the plugin to be shown on the f2 -> plugins list
std::string Disadvantages::GetPluginName()
{
	return "Disadvantages";
}

void Disadvantages::RenderSettings() {
	ImGui::TextUnformatted("Disadvantages by Ethy");

	CVarWrapper enableCvar = cvarManager->getCvar("isenabled_dis");

	if (!enableCvar) {
		return;
	}

	bool enabled = enableCvar.getBoolValue();

	if (ImGui::Checkbox("Enable plugin", &enabled)) {
		enableCvar.setValue(enabled);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Enable the Disadvantages Plugin");
	}

	CVarWrapper blueEnableCvar = cvarManager->getCvar("blueenabled_dis");

	if (!blueEnableCvar) {
		return;
	}

	bool bnabled = blueEnableCvar.getBoolValue();

	if (ImGui::Checkbox("Blue Disadvantage", &bnabled)) {
		blueEnableCvar.setValue(bnabled);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Enable Disadvantages for Blue");
	}

	CVarWrapper orangeEnableCvar = cvarManager->getCvar("orangeeenabled_dis");

	if (!orangeEnableCvar) {
		return;
	}

	bool onabled = orangeEnableCvar.getBoolValue();

	if (ImGui::Checkbox("Orange Disadvantage", &onabled)) {
		orangeEnableCvar.setValue(onabled);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Enable Disadvantages for Orange");
	}
	
	CVarWrapper intervalCvar = cvarManager->getCvar("interval_dis");

	if (!intervalCvar) {
		return;
	}

	float interval = intervalCvar.getFloatValue();
	if (ImGui::SliderFloat("Interval", &interval, 5.0f, 100.0f)) {
		intervalCvar.setValue(interval);
	}
	if (ImGui::IsItemHovered()) {
		std::string hoverText = "interval is " + std::to_string(interval);
		ImGui::SetTooltip(hoverText.c_str());
	}
}

/*
// Do ImGui rendering here
void Disadvantages::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

// Name of the menu that is used to toggle the window.
std::string Disadvantages::GetMenuName()
{
	return "Disadvantages";
}

// Title to give the menu
std::string Disadvantages::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool Disadvantages::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool Disadvantages::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void Disadvantages::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void Disadvantages::OnClose()
{
	isWindowOpen_ = false;
}
*/
