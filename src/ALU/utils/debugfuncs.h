#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

#include "../N.N/strvector.h"
#include "../../Dictionary/WIP.h"

#define WaitforEnter std::cout << "\n\nPress enter to continue . . . " << std::endl; std::cin.get();

namespace Debug
{
	void changeConsoleColor(int number)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, number);
	}

	void printVectorString(std::vector<std::string> vector)
	{
		std::cout << "{ ";
		for (int i = 0; i < vector.size(); i++)
		{
			if (i > 0)
				std::cout << ", ";
			std::cout << "[" << vector[i] << "]";
		}
		std::cout << " }";
	}

	void printStringVector(strvector vector)
	{
		std::cout << "{ ";
		for (int i = 0; i < vector.size(); i++)
		{
			if (i > 0)
				std::cout << ", ";
			std::cout << "[" << vector[i] << "]";
		}
		std::cout << " }";
	}

	void printRawString(strvector vector)
	{
		std::cout << vector.getRawString() << std::endl;
	}

	void printWIP(WordInfoPacket wip)
	{
		std::cout << "-------------------------------------------\n";
		std::cout << "WIP :: " << wip.word << std::endl;
		std::cout << "-------------------------------------------\n";
		std::cout << "Parts of speech: ";
		printVectorString(wip.pos);
		std::cout << "\nDefinitions: ";
		printVectorString(wip.defs);
		std::cout << "\nPlural form: " << wip.plural << std::endl;
		std::cout << "\nOther info: " << wip.otherInfo << std::endl;
		std::cout << "-------------------------------------------\n";
	}

}