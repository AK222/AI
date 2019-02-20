#pragma once

#include <string>
#include <vector>

struct WordInfoPacket
{
	std::string word;
	std::vector <std::string> defs;
	std::vector <std::string> pos;
	std::string plural;
	std::string otherInfo;
};