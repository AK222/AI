#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "debugfuncs.h"
#include "../../Dictionary/DictionaryLoader.h"
#include "../LTM - (Long Term Memory)/manageLTM.h"

namespace Test
{

	void tokenizeSentenceTEST()
	{
		std::vector<std::string> tokenized = Dictionary::tokenizeSentence("Hello, it's my : b-day today! [-pron.]");
		Debug::printVectorString(tokenized);
		std::cout << "\n";
	}

	void getWordInfoTEST()
	{
		std::string word = "FuNnY";
		std::string info = Dictionary::getWordInfo(word);
		if (info != "STR_NOT_FOUND")
			std::cout << info << std::endl;
		else
		{
			Debug::changeConsoleColor(FOREGROUND_RED);
			std::cerr << "The word " << word << " was not found in the dictionary." << std::endl;
			Debug::changeConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			WaitforEnter
		}
	}

	void createWIPTEST()
	{
		std::string word = "Funny";
		WordInfoPacket packet = Dictionary::createWIP(word.c_str());
		Debug::printWIP(packet);
	}

	void WIPtoANDfromStrvectorTEST()
	{
		std::string word = "Funny";
		WordInfoPacket packet = Dictionary::createWIP(word.c_str());
		Debug::printWIP(packet);
		std::cout << "\n";
		strvector strpacket = Dictionary::PacketToStrvec(packet);
		Debug::printStringVector(strpacket);
		std::cout << "\n";
		packet = Dictionary::StrvecToPacket(strpacket);
		Debug::printWIP(packet);
		std::cout << "\n";
	}

	void getWordInfoTEST2()
	{
		std::string word = "FuNnY";
		std::string info = LTM::Lingual::getWordInfo(word).getRawString();
		if (info != ".STR_NOT_FOUND.")
			std::cout << info << std::endl;
		else
		{
			Debug::changeConsoleColor(FOREGROUND_RED);
			std::cerr << "The word " << word << " was not found in the LTM." << std::endl;
			Debug::changeConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			WaitforEnter
		}
	}

	void getWordWIPTEST()
	{
		const char * word = "Funny";
		Debug::printWIP(LTM::Lingual::getWordWIP(word));
	}
}