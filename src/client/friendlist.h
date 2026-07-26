// Luanti
// SPDX-License-Identifier: LGPL-2.1-or-later
// MineBoostV2 friend system

#pragma once

#include <set>
#include <string>

// Simple persistent friend list used by the client-side ".friend" commands
// and by the friend ESP renderer. Names are matched case-insensitively but
// stored with their original casing for display purposes.
//
// Each server gets its own list (see setServer()), since a name that's a
// friend on one server has no particular relationship to the same name on
// a different server.
class FriendList
{
public:
	static FriendList &get();

	// Switches to the friend list for a given server, identified by a
	// caller-provided key (e.g. "hostname:port"). Called once on connect.
	// Safe to call redundantly; a no-op if already on that server's list.
	void setServer(const std::string &server_key);

	// Returns false if the name was already on the list.
	bool add(const std::string &name);

	// Returns false if the name was not on the list.
	bool remove(const std::string &name);

	bool isFriend(const std::string &name) const;

	const std::set<std::string> &getAll() const { return m_friends; }

private:
	FriendList();

	void load();
	void save() const;

	static std::string normalize(const std::string &name);
	static std::string sanitizeForFilename(const std::string &s);

	std::set<std::string> m_friends;       // normalized (lowercase) names
	std::set<std::string> m_friends_display; // original casing, for listing
	std::string m_path;
	std::string m_server_key; // empty until setServer() is called
};
