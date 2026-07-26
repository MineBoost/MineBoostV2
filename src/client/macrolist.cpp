// Luanti
// SPDX-License-Identifier: LGPL-2.1-or-later
// MineBoostV2 macro wheel

#include "macrolist.h"
#include "filesys.h"
#include "porting.h"
#include "util/string.h"
#include "log.h"
#include <cctype>
#include <fstream>

MacroList &MacroList::get()
{
	static MacroList instance;
	return instance;
}

MacroList::MacroList()
{
	// Fallback list used before we know which server we're on (e.g. if
	// something touches the list from the main menu). Once setServer()
	// is called this is replaced by a per-server list.
	m_path = porting::path_user + DIR_DELIM + "macros.txt";
	load();
}

std::string MacroList::sanitizeForFilename(const std::string &s)
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

void MacroList::setServer(const std::string &server_key)
{
	if (server_key == m_server_key)
		return; // already using this server's list

	// Persist whatever's currently loaded before switching away from it
	// (covers the fallback list, or the previous server if we're
	// reconnecting to a different one mid-session).
	save();

	m_server_key = server_key;
	m_path = porting::path_user + DIR_DELIM + "macros_" +
		sanitizeForFilename(server_key) + ".txt";

	m_macros.clear();
	load();
}

bool MacroList::add(const std::string &command)
{
	std::string trimmed(trim(command));
	if (trimmed.empty())
		return false;

	m_macros.push_back(trimmed);
	save();
	return true;
}

bool MacroList::removeIndex(size_t index_1based)
{
	if (index_1based == 0 || index_1based > m_macros.size())
		return false;

	m_macros.erase(m_macros.begin() + (index_1based - 1));
	save();
	return true;
}

void MacroList::clear()
{
	m_macros.clear();
	save();
}

void MacroList::load()
{
	std::ifstream is(m_path);
	if (!is.good())
		return;

	std::string line;
	while (std::getline(is, line)) {
		std::string trimmed(trim(line));
		if (trimmed.empty())
			continue;
		m_macros.push_back(trimmed);
	}
}

void MacroList::save() const
{
	std::ofstream os(m_path, std::ios::trunc);
	if (!os.good()) {
		warningstream << "MacroList: failed to write " << m_path << std::endl;
		return;
	}

	for (const auto &command : m_macros)
		os << command << "\n";
}
