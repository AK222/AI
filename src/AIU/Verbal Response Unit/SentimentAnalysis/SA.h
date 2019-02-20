#pragma once

#include <string>

#include "../../../ALU/LTM - (Long Term Memory)/manageLTM.h"

std::string getExpressed(std::string word, bool truncate = false, bool isWord = true)
{
	std::vector<std::string> expresses;
	std::vector<std::string> defs;
	if (isWord)
		defs = LTM::Lingual::getWordWIP(word.c_str()).defs;
	else
	{
		strvector vec; vec.set(word);
		if (vec.getRawString() != ".STR_NOT_FOUND.")
			defs = Dictionary::StrvecToPacket(vec).defs;
		else
			return "";
	}
	for (int i = 0; i < defs.size(); i++)
	{
		std::vector<std::string> tokens = Dictionary::tokenizeSentence(defs[i]);
		for (int j = 0; j < tokens.size(); j++)
		{
			if (tokens[j].find("express") != -1 || tokens[j].find("feel") != -1)
			{
				j++;
				if (tokens[j] == "or")
					j++;
				while (j < tokens.size())
				{
					if (tokens[j].find("show") == -1)
					{
						expresses.push_back(tokens[j]);
						expresses.push_back(", ");
						j++;
					}
					j++;
				}
			}
		}
	}

	std::string final = "";
	if (!truncate)
		final = word + " expresses ";
	for (int i = 1; i < expresses.size(); i++)
	{
		final.append(expresses[i - 1]);
	}
	return final;
}

std::string performSentimentAnalysis(std::string passage, bool debugMode = false)
{
	bool first = true;
	std::vector <std::string> tokens = Dictionary::tokenizeSentence(passage);
	std::vector <std::string> potWords;
	std::vector <strvector> vecs;
	std::vector <int> locs;
	std::string final;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].size() > 3 && tokens[i].find("feel") == -1)
		{
			for (int j = 0; j < PUNC_SIZE; j++)
				std::replace(tokens[i].begin(), tokens[i].end(), Dictionary::punctuation[i], ' ');

			int count = 0;
			for (int j = 0; tokens[i][j]; j++)
				if (tokens[i][j] != ' ')
					tokens[i][count++] = tokens[i][j];
			tokens[i][count] = '\0';

			potWords.push_back(tokens[i]);
			locs.push_back(i);
		}
	}

	vecs = LTM::Lingual::getWordInfos(potWords);//, true);
	bool checkReached = false;
	for (int i = 0; i < vecs.size(); i++)
	{
		if (vecs[i].getRawString().find("|aux |") == -1 && vecs[i].getRawString().find("|aux|"))
		{
			std::string expresses = getExpressed(vecs[i].getRawString(), true, false);
			if (expresses != "")
			{
				if (!first)
					final.append(", ");
				if (debugMode)
					final.append(tokens[i] + ' ');
				if (locs[i] - 3 >= 0)
				{
					if (tokens[locs[i] - 1] == "not" || tokens[locs[i] - 2] == "not" || tokens[locs[i] - 3] == "not")
						final.append("does not express ");
					else
						final.append("expresses ");
					checkReached = true;
				}
				else if (locs[i] - 2 >= 0)
				{
					if (tokens[locs[i] - 1] == "not" || tokens[locs[i] - 2] == "not")
						final.append("does not express ");
					else
						final.append("expresses ");
					checkReached = true;
				}
				else if (locs[i] - 1 >= 0)
				{
					if (tokens[locs[i] - 1] == "not")
						final.append("does not express ");
					else
						final.append("expresses ");
					checkReached = true;
				}
				if (checkReached == false)
					final.append("expresses ");
				final.append(expresses);
				first = false;
			}
			checkReached = false;
		}
	}
	return final;
}