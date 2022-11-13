#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class Disadvantages : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow
{
    virtual void onLoad();
    virtual void onUnload();
    void tick();
    int timeUntilSecond = 120, playerTime = 15, ballTime = 15, count = 1;

    void updateBall(ServerWrapper server);
    void updatePlayers(ServerWrapper server);
    void updateCount(ServerWrapper server);

    void RenderSettings() override;
    std::string GetPluginName() override;
    void SetImGuiContext(uintptr_t ctx) override;
};