#pragma once
#include <string>
#include <iostream>
#include <vector>

class Dog
{
private:

	std::string breed;
	std::string name;
	int age;
	std::string link;

public:
	Dog() : name{ "" }, breed{ "" }, age{ 0 }, link{ "" } {}
	Dog(const std::string breed, const std::string name, const int age, const std::string link);

	std::string getBreed() const;
	std::string getName() const;
	int getAge() const;
	std::string getLink() const;

	void setBreed(std::string newbreed);
	void setAge(int newage);
	void setLink(std::string newlink);

	bool operator==(const Dog& dog);
	Dog& operator=(const Dog& dog)
	{
		this->breed = dog.breed;
		this->name = dog.name;
		this->age = dog.age;
		this->link = dog.link;
		return *this;
	}
	std::string str();
	/*
	Splits a string into a vector of strings based on a delimiter.
	*/
	std::vector<std::string> split(std::string str, char delimiter);

	/*
	Override function to read from a stream an object of type Dog.
	*/
	friend std::istream& operator>>(std::istream& stream, Dog& d);

	/*
	Override function to write to a stream an object of type Dog.
	*/
	friend std::ostream& operator<<(std::ostream& stream, const Dog& d);

};
