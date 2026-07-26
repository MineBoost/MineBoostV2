// Luanti
// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright (C) 2010-2013 celeron55, Perttu Ahola <celeron55@gmail.com>
// Copyright (C) 2018 nerzhul, Loic Blot <loic.blot@unix-experience.fr>

#pragma once

#include "irrlichttypes.h"
#include <IGUIEnvironment.h>
#include "game.h"

using namespace irr;
class Client;
class EnrichedString;
class GUIChatConsole;
struct MapDrawControl;
struct PointedThing;

/*
 * This object intend to contain the core UI elements
 * It includes:
 *   - status texts
 *   - debug texts
 *   - chat texts
 *   - hud flags
 */
class GameUI
{
	// Temporary between coding time to move things here
	friend class Game;

	// Permit unittests to access members directly
	friend class TestGameUI;

public:
	GameUI();
	~GameUI() = default;

	// Flags that can, or may, change during main game loop
	struct Flags
	{
		bool show_chat = true;
		bool show_hud = true;
		bool show_minimal_debug = false;
		bool show_basic_debug = false;
		bool show_profiler_graph = false;
	};

	void init();
	void update(const RunStats &stats, Client *client, MapDrawControl *draw_control,
			const CameraOrientation &cam, const PointedThing &pointed_old,
			const GUIChatConsole *chat_console, float dtime);

	void initFlags();
	const Flags &getFlags() const { return m_flags; }

	inline void setInfoText(const std::wstring &str) { m_infotext = str; }
	inline void clearInfoText() { m_infotext.clear(); }

	inline void showStatusText(const std::wstring &str)
	{
		m_statustext = str;
		m_statustext_time = 0.0f;
	}
	void showTranslatedStatusText(const char *str);
	inline void clearStatusText() { m_statustext.clear(); }

	bool isChatVisible()
	{
		return m_flags.show_chat && m_recent_chat_count != 0 && m_profiler_current_page == 0;
	}
	void setChatText(const EnrichedString &chat_text, u32 recent_chat_count);
	void updateChatSize();

	void updateProfiler();

	void toggleChat(Client *client);
	void toggleHud();
	void toggleProfiler();

	void clearText();

private:
	Flags m_flags;

	float m_drawtime_avg = 0;

	// Debug/overlay text like coords, FPS and ping only needs to be
	// legible, not updated every single rendered frame -- re-shaping a
	// GUI text label (word wrap, glyph layout) on every call is wasted
	// work at high frame rates and adds up on weak hardware. These throttle
	// the actual setText()/relayout calls to a fixed real-time interval,
	// independent of the current FPS, while the label's on-screen position
	// still follows drag/settings changes every frame (cheap).
	static constexpr float HUD_TEXT_UPDATE_INTERVAL = 0.2f; // 5 updates/sec
	float m_coords_text_timer = HUD_TEXT_UPDATE_INTERVAL;
	float m_fps_text_timer = HUD_TEXT_UPDATE_INTERVAL;
	float m_ping_text_timer = HUD_TEXT_UPDATE_INTERVAL;

	// Global size multiplier for MineBoost's custom HUD elements (see
	// "hud_size" in src/gui/custom_menu/Menu.cpp, "HUD Size" slider),
	// each combined with its own independent per-element multiplier
	// ("coords_size"/"fps_size"/"ping_size", adjustable by scrolling over
	// the element while in "Move HUD" edit mode). Cached per-element so
	// each font is only rebuilt when its own combined value changes.
	float m_last_coords_size = -1.0f;
	float m_last_fps_size = -1.0f;
	float m_last_ping_size = -1.0f;

	gui::IGUIStaticText *m_guitext = nullptr;  // First line of debug text
	gui::IGUIStaticText *m_guitext2 = nullptr; // Second line of debug text

	gui::IGUIStaticText *m_guitext_info = nullptr; // At the middle of the screen
	gui::IGUIStaticText *m_guitext_coords = nullptr;
	gui::IGUIStaticText *m_guitext_showfps = nullptr;
	gui::IGUIStaticText *m_guitext_showping = nullptr;
	std::wstring m_infotext;

	gui::IGUIStaticText *m_guitext_status = nullptr;
	std::wstring m_statustext;
	float m_statustext_time = 0.0f;
	video::SColor m_statustext_initial_color;

	gui::IGUIStaticText *m_guitext_chat = nullptr; // Chat text
	u32 m_recent_chat_count = 0;
	core::rect<s32> m_current_chat_size{0, 0, 0, 0};

	gui::IGUIStaticText *m_guitext_profiler = nullptr; // Profiler text
	u8 m_profiler_current_page = 0;
	const u8 m_profiler_max_page = 3;
};
