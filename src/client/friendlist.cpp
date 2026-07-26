// Luanti
// SPDX-License-Identifier: LGPL-2.1-or-later
// MineBoostV2 friend system

#include "friendlist.h"
#include "filesys.h"
#include "porting.h"
#include "util/string.h"
#include "log.h"
#include <cctype>
#include <fstream>

FriendList &FriendList::get()
{
	static FriendList instance;
	return instance;
}

FriendList::FriendList()
{
	// Fallback list used before we know which server we're on (e.g. if
	// something touches the list from the main menu). Once setServer()
	// is called this is replaced by a per-server list.
	m_path = porting::path_user + DIR_DELIM + "friends.txt";
	load();
}

std::string FriendList::normalize(const std::string &name)
{
	return lowercase(trim(name));
}

std::string FriendList::sanitizeForFilename(const std::string &s)
{
	std::string out;
	out.reserve(s.size());
	for (char c : s) {
		if (isalnum((unsigned char)c) || c == '.' || c == '-' || c == '_')
			out += c;
		else
			out += '_';
	}
	return out;
}

void FriendList::setServer(const std::string &server_key)
{
	if (server_key == m_server_key)
		return; // already using this server's list

	// Persist whatever's currently loaded before switching away from it
	// (covers the fallback list, or the previous server if we're
	// reconnecting to a different one mid-session).
	save();

	m_server_key = server_key;
	m_path = porting::path_user + DIR_DELIM + "friends_" +
		sanitizeForFilename(server_key) + ".txt";

	m_friends.clear();
	m_friends_display.clear();
	load();
}

bool FriendList::add(const std::string &name)
{
	std::string trimmed(trim(name));
	if (trimmed.empty())
		return false;

	std::string key = normalize(trimmed);
	auto result = m_friends.insert(key);
	if (!result.second)
		return false; // already a friend

	m_friends_display.insert(trimmed);
	save();
	return true;
}

bool FriendList::remove(const std::string &name)
{
	std::string key = normalize(name);
	if (m_friends.erase(key) == 0)
		return false;

	// Remove the matching display entry too.
	for (auto it = m_friends_display.begin(); it != m_friends_display.end(); ++it) {
		if (normalize(*it) == key) {
			m_friends_display.erase(it);
			break;
		}
	}

	save();
	return true;
}

bool FriendList::isFriend(const std::string &name) const
{
	return m_friends.count(normalize(name)) != 0;
}

void FriendList::load()
{
	std::ifstream is(m_path);
	if (!is.good())
		return;

	std::string line;
	while (std::getline(is, line)) {
		std::string trimmed(trim(line));
		if (trimmed.empty())
			continue;
		m_friends.insert(normalize(trimmed));
		m_friends_display.insert(trimmed);
	}
}

void FriendList::save() const
{
	std::ofstream os(m_path, std::ios::trunc);
	if (!os.good()) {
		warningstream << "FriendList: failed to write " << m_path << std::endl;
		return;
	}

	for (const auto &name : m_friends_display)
		os << name << "\n";
}
