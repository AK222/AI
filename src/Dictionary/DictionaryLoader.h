#pragma once

#include <fstream>
#include <iostream>
#include <locale>
#include <algorithm>

#include "../ALU/utils/debugfuncs.h"
#include "WIP.h"
#include "../ALU/N.N/strvector.h"
#include "../ALU/LTM - (Long Term Memory)/Lingual/LetterIndices.h"

namespace Dictionary
{
	//If you add punctuation remember to change the punctuation size below
	char punctuation[] = { '.', ',', '?', '!', '\'', '"', ':', ';', '-', '_', '(', ')', '[', ']', '{', '}' };
#define PUNC_SIZE 16

	void alphabetize(std::vector<std::string> * words)
	{
		std::sort(words->begin(), words->end());
	}

	bool isBefore(std::string before, std::string after, bool incSame = false)
	{
		if (incSame)
			return before <= after;
		return before < after;
	}

	std::vector<std::string> tokenizeSentence(std::string str)
	{
		std::vector<std::string> tokens;
		std::string word = "";
		for (char x : str)
		{
			if (x == ' ')
			{
				tokens.push_back(word);
				word = "";
			}
			else
			{
				word = word + x;
			}
		}
		tokens.push_back(word);

		int count = 0;
		for (int i = 0; i < tokens.size(); i++)
		{
			for (int j = 0; j < PUNC_SIZE; j++) // punctuation size
			{
				int found = tokens[i].find(punctuation[j]);
				if (found >= 0)
				{
					std::string term1 = tokens[i].substr(0, found);
					std::string term2 = "";
					term2.push_back(punctuation[j]);
					std::string term3 = "";
					if (tokens[i].length() > found + 1)
						term3 = tokens[i].substr(found + 1);
					if (term3 == "" && term1 != "")
					{
						tokens[i] = term1;
						tokens.insert(tokens.begin() + i + 1, term2);
						count++;
					}
					else if (term1 == "" && term3 != "")
					{
						tokens[i] = term2;
						tokens.insert(tokens.begin() + i + 1, term3);
						i++;
					}
				}
			}
			i += count;
			count = 0;
		}
		return tokens;
	}

	// Function for finding related words and synonyms from defs
	std::string lowercase(std::string str)
	{
		std::locale loc;
		std::string result;
		for (int i = 0; i < str.length(); ++i)
			result.push_back(std::tolower(str[i], loc));
		return result;
	}

	std::string getWordInfo(std::string word)
	{
		std::ifstream inFile;
		inFile.open("src/Dictionary/Dictionary.txt", std::ifstream::in);
		if (!inFile.is_open()) std::cerr << "[ERROR] COULD NOT OPEN FILE!";
		char firstLetter = lowercase(word)[0];
		std::string temp;
		while (std::getline(inFile, temp))
		{
			// First save a completely uncapitalized version of temp in superTemp
			std::string superTemp = lowercase(temp);
			if (superTemp.find(lowercase(word)) == 0) //<-- To find related words just set this to > 0
				return temp;
			if (superTemp[0] > firstLetter && superTemp.find("usage") == -1)
				return std::string("STR_NOT_FOUND");
		}
		inFile.close();
		return std::string("STR_NOT_FOUND");
	}

	WordInfoPacket createWIP(std::string totalInfo)
	{
		WordInfoPacket packet;

		// Scan for "n", "pron", "v", "adj", "adv", "prep", "int", "conj"
		std::string POS[] = { "n", "pron", "v", "adj", "adv", "prep", "int", "conj" };
		std::vector <std::string> vec = tokenizeSentence(totalInfo);
		std::vector <short> usedInfo;
		usedInfo.push_back(0);

		// Set packet.word
		packet.word = vec[0];
		// Set packet.pos
		if (totalInfo.find("prefix") != -1)
			packet.pos.push_back("prefix");
		else
		{
			for (int i = 0; i < vec.size(); i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (vec[i] == POS[j])
					{
						packet.pos.push_back(POS[j]);
						usedInfo.push_back(i);
					}
				}
			}
		}
		for (int i = usedInfo.size() - 1; i >= 0; i--)
			vec.erase(vec.begin() + usedInfo[i]);
		usedInfo.clear();
		// Set packet.defs
		bool read = true;
		std::string defTokens = "";
		for (int i = 0; i < vec.size(); i++)
		{
			if (read)
			{
				if (vec[i] == "[" || vec[i] == "(" || vec[i] == "{")
					read = false;
				else if (vec[i] != ".")
				{
					defTokens.append(vec[i] + " ");
					usedInfo.push_back(i);
				}
				else
				{
					defTokens.append(" | ");
					usedInfo.push_back(i);
				}
			}
			if (vec[i] == "]" || vec[i] == ")" || vec[i] == "}")
				read = true;
		}
		for (int i = usedInfo.size() - 1; i >= 0; i--)
			vec.erase(vec.begin() + usedInfo[i]);
		int found = 1;
		while (found > 0)
		{
			found = defTokens.find('|');
			if (found > 0)
			{
				std::string def = defTokens.substr(0, found);
				defTokens.erase(defTokens.begin(), defTokens.begin() + found + 1);
				if (def[0] == ' ')
					def.erase(def.begin());
				if (!(def == ""))
					if (def[def.length() - 1] == ' ')
						def.pop_back();
				if (def.length() > 2)
					packet.defs.push_back(def);
			}
		}
		// Set packet.plural
		packet.plural = packet.word + 's';
		// Set packet.otherInfo
		for (int i = 0; i < vec.size(); i++)
			packet.otherInfo.append(vec[i] + " ");

		return packet;
	}

	WordInfoPacket createWIP(const char * word)
	{
		std::string totalInfo = getWordInfo(std::string(word));
		return createWIP(totalInfo);
	}

	strvector PacketToStrvec(WordInfoPacket packet)
	{
		strvector defs(packet.defs);
		strvector pos(packet.pos);

		std::string fdefs = defs.getRawString();
		std::replace(fdefs.begin(), fdefs.end(), '.', '|');
		std::string fpos = pos.getRawString();
		std::replace(fpos.begin(), fpos.end(), '.', '|');
		std::string fOI = packet.otherInfo;
		std::replace(fOI.begin(), fOI.end(), '.', '~');

		strvector result;
		result.push_back(packet.word);
		result.push_back(fdefs);
		result.push_back(fpos);
		result.push_back(packet.plural);
		result.push_back(fOI);

		return result;
	}

	WordInfoPacket StrvecToPacket(strvector packet)
	{
		WordInfoPacket result;
		if (packet.size() != 5)
		{
			Debug::changeConsoleColor(FOREGROUND_RED);
			std::cerr << "[ERROR] Something went wrong when loading a WordInfoPacket from a strvector!\n";
			Debug::changeConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			WaitforEnter
		}
		result.word = packet[0];

		std::string fdefs = packet[1];
		std::replace(fdefs.begin(), fdefs.end(), '|', '.');
		strvector vec;
		vec.set(fdefs);
		std::vector <std::string> fvec = vec.getstdVectorofString();
		result.defs = fvec;

		std::string fpos = packet[2];
		std::replace(fpos.begin(), fpos.end(), '|', '.');
		strvector vec2;
		vec2.set(fpos);
		std::vector <std::string> fvec2 = vec2.getstdVectorofString();
		result.pos = fvec2;

		result.plural = packet[3];

		std::string fOI = packet[4];
		std::replace(fOI.begin(), fOI.end(), '~', '.');
		result.otherInfo = fOI;

		return result;
	}

	// BOOTUP function that stores the Dictionary as wordpackets into Total.WIP if Total.WIP is empty and also updates relationIDs after that. TAKES ONLY AROUND 4.5 min!
	void BOOTUP() // TODO: Switch non-ASCII characters with similar ASCII characters . . . 
	{
		initMap();
		int ln = 1;
		std::string temp1;
		std::ofstream outFile;
		std::ifstream inFile;
		inFile.open("src/ALU/LTM - (Long Term Memory)/Lingual/Total.WIP", std::ifstream::in);
		if (!inFile.is_open())
			std::cerr << "Could not open Bootup files!";
		if (!(std::getline(inFile, temp1)))
		{
			outFile.open("src/ALU/LTM - (Long Term Memory)/Lingual/Total.WIP", std::ofstream::out | std::ofstream::trunc);
			if (!outFile.is_open())
				std::cerr << "Could not open Bootup files!";
			inFile.close();
			inFile.open("src/Dictionary/Dictionary.txt", std::ifstream::in);
			if (!inFile.is_open()) std::cerr << "[ERROR] COULD NOT OPEN FILE!";
			std::string temp;
			while (std::getline(inFile, temp))
			{
				int tempI = temp.find("Usage");
				if (((tempI < 0) || (ln == 68529)) && temp.size() > 2)
				{
					WordInfoPacket WIP = createWIP((std::string)temp);
					strvector vec = PacketToStrvec(WIP);
					outFile << WIP.word << "\n";
					outFile << vec.getRawString();
					outFile << "\n";
					outFile << "----------------------------------------------------------------------------------------------------------\n";
					std::cout << WIP.word << "\n";
					std::cout << vec.getRawString();
					std::cout << "\n";
					std::cout << "----------------------------------------------------------------------------------------------------------\n";
				}
				ln++;
			}
			outFile.close();
		}
		inFile.close();

		// NOW TO SET UP THE RELATIOND IDs
		inFile.open("src/ALU/LTM - (Long Term Memory)/Lingual/RelationID.txt", std::ifstream::in);
		if (!inFile.is_open())
			std::cerr << "Could not open Bootup files!";
		if (!(std::getline(inFile, temp1)))
		{
			outFile.open("src/ALU/LTM - (Long Term Memory)/Lingual/RelationID.txt", std::ofstream::out | std::ofstream::trunc);
			if (!outFile.is_open())
				std::cerr << "Could not open Bootup files!";
			inFile.close();
			inFile.open("src/ALU/LTM - (Long Term Memory)/Lingual/Total.WIP", std::ifstream::in);
			if (!inFile.is_open()) std::cerr << "[ERROR] COULD NOT OPEN FILE!";
			// TODO
		}
	}

	// Function that watches for word use and stores the top 100 used words in Common.WIP

	// Using first function set up RelationID

	// New word loader in the middle of the app that can take in defs, part of speechs, and words and add them to the dictionary at the right place

	// In AIU define a function that can determine the part of speech of a word from a sentence

	// In AIU make functions to harvest info from RelationID.txt and Words.txt

	// LATER make a web scraper for new words
}