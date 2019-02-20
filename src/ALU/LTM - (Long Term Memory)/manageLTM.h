#pragma once

#include "../N.N/strvector.h"
#include "../../Dictionary/DictionaryLoader.h"

#include <fstream>

#include "../LTM - (Long Term Memory)/Lingual/LetterIndices.h"

namespace LTM
{
	namespace Lingual
	{
		strvector getWordInfo(std::string word)
		{
			std::ifstream inFile;
			std::string temp;
			inFile.open("src/ALU/LTM - (Long Term Memory)/Lingual/Total.WIP");
			if (!inFile) std::cerr << "SOMETHING WENT WRONG: TOTAL.WIP COULD NOT BE FOUND!" << std::endl;
			char firstLletter = Dictionary::lowercase(word)[0];
			for (int i = 1; i < letterMap[firstLletter]; i++)
				std::getline(inFile, temp);
			while (std::getline(inFile, temp))
			{
				if (Dictionary::lowercase(temp) == Dictionary::lowercase(word))
				{
					std::getline(inFile, temp);
					strvector info;
					info.set(temp);
					inFile.close();
					return info;
				}
			}
			inFile.close();
			strvector info;
			info.set(".STR_NOT_FOUND.");
			return info;
		}

		std::vector <strvector> getWordInfos(std::vector<std::string> words, bool should = false)
		{
			std::vector <strvector> result;
			// TESTING PURPOSES ONLY
			if (should)
			{
				for (int i = 0; i < words.size(); i++)
				{
					result.push_back(getWordInfo(words[i]));
				}
				return result;
			}

			strvector info;
			std::string temp;
			info.set(".STR_NOT_FOUND.");
			for (int i = 0; i < words.size(); i++)
				result.push_back(info);

			int wordNum = 0;

			// Make all the words lowercase
			for (int i = 0; i < words.size(); i++)
				words[i] = Dictionary::lowercase(words[i]);

			// Arrange the words in alphabetical order 
			Dictionary::alphabetize(&words);

			// Open the dictionary
			std::ifstream inFile;
			inFile.open("src/ALU/LTM - (Long Term Memory)/Lingual/Total.WIP");

			int line = 0;

			// Figure out the starting letter of the first word and put all the letters with that starting letter into another vector
			while (!(words.size() == 0))
			{
				char startingLetter = Dictionary::lowercase(words[0])[0];
				std::vector <std::string> currentWords;
				for (int i = 0; i < words.size(); i++)
				{
					if (Dictionary::lowercase(words[i])[0] == startingLetter)
					{
						currentWords.push_back(words[i]);
						words.erase(words.begin() + i);
						i--;
					}
					else
					{
						break;
					}
				}

				// Go to the starting letter in the dictionary
				for (int j = line; j < letterMap[startingLetter]; j++)
				{
					std::getline(inFile, temp);
					line++;
				}

				// Find each of those words in the dictionary
				for (int i = 0; i < currentWords.size(); i++)
				{
					// While the word is alphabetically before temp, look for it
					while (std::getline(inFile, temp) && Dictionary::isBefore(Dictionary::tokenizeSentence(Dictionary::lowercase(temp))[0], currentWords[i], true))
					{
						line++;
						info.set(temp);
						if (info.exists(0))
						{
							if (Dictionary::lowercase(info[0]) == Dictionary::lowercase(currentWords[i]))
							{
								result[wordNum] = info;
							}
						}
					}
					wordNum++;
				}
			}
			// Close the dictionary
			inFile.close();

			return result;
		}

		WordInfoPacket getWordWIP(std::string wordInfo)
		{
			strvector info;
			info.set(wordInfo);
			return Dictionary::StrvecToPacket(info);
		}

		WordInfoPacket getWordWIP(const char * word)
		{
			return getWordWIP(getWordInfo(word).getRawString());
		}

		std::vector <WordInfoPacket> getWordWIPs(std::vector<std::string> words)
		{
			std::vector <WordInfoPacket> result;
			std::vector <strvector> preResult = getWordInfos(words);
			for (int i = 0; i < preResult.size(); i++)
				result.push_back(Dictionary::StrvecToPacket(preResult[i]));
			return result;
		}

		std::vector<std::string> EXSimilarWords(std::string word)
		{
			std::vector <std::string> exSim;

			WordInfoPacket WIP = LTM::Lingual::getWordWIP(word.c_str());
			std::vector <std::string> defs = WIP.defs;
			for (int i = 0; i < defs.size(); i++)
			{
				std::vector <std::string> tokens = Dictionary::tokenizeSentence(defs[i]);
				for (int j = 0; j < tokens.size(); j++)
				{
					WordInfoPacket oWIP = LTM::Lingual::getWordWIP(tokens[j]);
					if (oWIP.pos == WIP.pos)
						exSim.push_back(oWIP.word);
				}
			}

			return exSim;
		}
	}
}