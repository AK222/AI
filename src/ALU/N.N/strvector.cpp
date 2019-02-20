#include "strvector.h"

strvector::strvector()
{
}

strvector::strvector(std::vector<std::string> vec)
{
	for (int i = 0; i < vec.size(); i++)
		this->push_back(vec[i]);
}

strvector::~strvector()
{
}

void strvector::set(std::string stringtoset)
{
	StrVector = stringtoset;
}

std::string strvector::element(unsigned int location)
{
	unsigned int count = 0;
	int found;
	found = StrVector.find(".");
	count++;
	while (count < location + 1)
	{
		found = StrVector.find(".", found + 1);
		count++;
	}
	int found2 = StrVector.find(".", found + 1);
	if (found2 == StrVector.npos)
	{
		std::cerr << "ERR_OUT_OF_RANGE: Vector element index out of range";
	}
	std::string element = StrVector.substr(found + 1, found2 - found - 1);
	return element;
}

std::string strvector::operator[](unsigned int location)
{
	return this->element(location);
}

std::string strvector::first()
{
	return this->element(0);
}

std::string strvector::last()
{
	return this->element(this->size() - 1);
}

unsigned int strvector::find(std::string stringtofind)
{
	return StrVector.find(stringtofind);
}

int strvector::size()
{
	int count = 0;
	int found;
	found = StrVector.find(".");
	count++;
	while (found != StrVector.npos)
	{
		found = StrVector.find(".", found + 1);
		count++;
	}
	return count - 2;
}

bool strvector::empty()
{
	if (StrVector == ".")
		return true;
	else
		return false;
}

void strvector::clear()
{
	this->set(".");
}

bool strvector::exists(unsigned int location)
{
	unsigned int count = 0;
	int found;
	found = StrVector.find(".");
	count++;
	while (count < location + 1)
	{
		found = StrVector.find(".", found + 1);
		count++;
	}
	int found2 = StrVector.find(".", found + 1);
	if (found2 == StrVector.npos)
	{
		return false;
	}
	return true;
}

void strvector::push_back(std::string stringtopush)
{
	StrVector.append(stringtopush);
	StrVector.append(".");
}

void strvector::pop_back()
{
	int count = 0;
	int found;
	found = StrVector.find(".");
	count++;
	while (count < this->size())
	{
		found = StrVector.find(".", found + 1);
		count++;
	}
	int found2 = StrVector.find(".", found + 1);
	StrVector.erase(found + 1, found2);
}

void strvector::remove(std::string stringtoremove)
{
	StrVector.erase(StrVector.find(stringtoremove) - 1, stringtoremove.size() + 1);
}

strvector strvector::getletters()
{ 
	strvector letters;
	for (int i = 0; i < this->size(); i++)
	{
		std::string str = this->element(i);
		const char * cstr = str.c_str();

		if (isalpha(cstr[0]))
			letters.push_back(this->element(i));
	}
	return letters;
}

strvector strvector::getnumbers()
{
	strvector numbers;
	for (int i = 0; i < this->size(); i++)
	{
		std::string str = this->element(i);
		const char * cstr = str.c_str();

		if (isdigit(cstr[0]))
			numbers.push_back(this->element(i));
	}
	return numbers;
}

std::string strvector::getRawString()
{
	return StrVector;
}

std::vector<std::string> strvector::getstdVectorofString()
{
	std::vector <std::string> result;
	for (int i = 0; i < this->size(); i++)
		result.push_back(this->element(i));
	return result;
}
