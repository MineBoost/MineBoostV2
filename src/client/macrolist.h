// Luanti
// SPDX-License-Identifier: LGPL-2.1-or-later
// MineBoostV2 macro wheel

#pragma once

#include <string>
#include <vector>

// Ordered, persistent list of commands used by the "Macro Wheel" (see
// KeyType::MACRO_WHEEL / hud->drawMacroWheel()). Populated via the
// client-side ".macro add <command>" chat command. Holding the wheel key
// (default Tab) pops the wheel up; scrolling the mouse wheel while it's
// held cycles through these entries; releasing the key sends whichever
// one is selected exactly as if it had been typed in chat (so it can be
// a "/server_command", a plain chat message, or even another client-side
// "." command).
//
// Each server gets its own list (see setServer()), same rationale as
// FriendList -- a macro that makes sense on one server (e.g. a specific
// "/kit" name) usually doesn't on another.
class MacroList
{
public:
	static MacroList &get();

	// Switches to the macro list for a given server, identified by a
	// caller-provided key (e.g. "hostname:port"). Called once on connect.
	// Safe to call redundantly; a no-op if already on that server's list.
	void setServer(const std::string &server_key);

	// Appends a command to the end of the list. Returns false only if
	// the command is empty.
	bool add(const std::string &command);

	// Removes by 1-based index (as shown in ".macro list"). Returns
	// false if the index is out of range.
	bool removeIndex(size_t index_1based);

	void clear();

	const std::vector<std::string> &getAll() const { return m_macros; }

private:
	MacroList();

	void load();
	void save() const;

	static std::string sanitizeForFilename(const std::string &s);

	std::vector<std::string> m_macros;
	std::string m_path;
	std::string m_server_key; // empty until setServer() is called
};
