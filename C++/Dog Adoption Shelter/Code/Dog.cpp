#include "Dog.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

//Dog::Dog()
//{
//}

Dog::Dog(std::string breed, std::string name, int age, std::string link)
{
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->link = link;
}

std::string Dog::getBreed() const
{
	return breed;
}

std::string Dog::getName() const
{
	return name;
}

int Dog::getAge() const
{
	return age;
}

std::string Dog::getLink() const
{
	return link;
}

void Dog::setBreed(std::string newbreed)
{
	this->breed = newbreed;
}

void Dog::setAge(int newage)
{
	this->age = newage;
}

void Dog::setLink(std::string newlink)
{
	this->link = newlink;
}

bool Dog::operator==(const Dog& dog)
{
	/*
	if (this->age == dog.age && this->name == dog.name && this->breed == dog.breed && this->link == dog.link)
		return true;
	return false;
	*/
	if (this->name == dog.name)
		return true;
	return false;
}

std::string Dog::str()
{
	std::string str = "";
	str = str + "Name: " + this->getName() + "; Breed: " + this->getBreed() + "; Age: " + std::to_string(this->getAge()) + "; Link: " + this->getLink();
	//	std::cout << "Name: " << this->getName() << "; Breed: " << this->getBreed() << "; Age: " << this->getAge() << "; Link: " << this->getLink() << " \n";
	return str;
}

std::vector<std::string> Dog::split(std::string str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter))
	{
		result.push_back(token);
	}
	return result;
}

std::istream& operator>>(std::istream& stream, Dog& d)
{
	//stream >> d.name >> d.breed >> d.age >> d.link;
	//stream.clear();
	//stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
	/*
	std::string line;
	std::getline(stream, line);
	
	std::vector<std::string> tokens;
	tokens = d.split(line, '|');

	if (tokens.size() == 4)
	{
		d.name = tokens[0];
		d.breed = tokens[1];
		d.age = std::stoi(tokens[2]);
		d.link = tokens[3];
		return stream;
	}
	else 
	{	
		stream >> d.name >> d.breed >> d.age >> d.link;
		return stream;
	}
	*/

	std::string line;
	std::getline(stream, line, '\n');
	std::vector<std::string> tokens;
	tokens = d.split(line, ',');
	if (tokens.size() != 4)
		return stream;
	d.name = tokens[0];
	d.breed = tokens[1];
	d.age = std::stoi(tokens[2]);
	d.link = tokens[3];
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Dog& d)
{
	//stream <<std::setw(5)<<std::left<< d.name+" |";
	//stream << std::setw(10) <<std::left<< d.breed + " |";
	//std::stringstream strWeight;

	//strWeight << d.age;
	//stream << std::setw(5) << std::left<< strWeight.str() + " |";
	//stream <<std::setw(5) <<std::left << d.link;
	//stream << d.name << "|" << d.breed << "|" << d.age << "|" << d.link;
	stream << d.name << "," << d.breed << "," << d.age << "," << d.link;
	return stream;
}
