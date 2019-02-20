#pragma once

#include <string>
#include <iostream>
#include <vector>

class strvector
{
private:
	std::string StrVector = ".";
public:
	// GENERAL METHODS:
	strvector();
	strvector(std::vector<std::string> vec);
	~strvector();

	void set(std::string stringtoset);

	std::string operator[](unsigned int location);
	
	std::string first();
	std::string last();

	unsigned int find(std::string stringtofind);

	int size();
	bool empty();
	void clear();
	bool exists(unsigned int location);

	void push_back(std::string stringtopush);
	void pop_back();
	void remove(std::string stringtoremove);

	strvector getletters();
	strvector getnumbers();

	std::string getRawString();

	std::vector <std::string> getstdVectorofString();

private:
	std::string element(unsigned int location);

};