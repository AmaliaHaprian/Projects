#include "Repository.h"
#include <stdexcept>
#include <fstream>
#include "ValidationException.h"

int Repository::searchRepo(std::string name)
{
	Dog d{ "", name, 0, "" };
	auto it = std::find(this->arr.begin(), this->arr.end(), d);
	if (it != this->arr.end()) {
		return std::distance(this->arr.begin(), it);
	}
	return -1;
}

bool Repository::removeRepo(std::string name)
{
	Dog d{ "", name, 0, ""};
	auto it = std::find(this->arr.begin(), this->arr.end(), d);
	if (it != this->arr.end()) {
		this->arr.erase(it);
		this->save();
		return true;
	}
	throw ValidationException("Dog not found in the shelter");
}

Repository Repository::getRepo()
{
	return *this;
}

int Repository::lengthRepo()
{
	return this->arr.size();
}

Dog Repository::getDog(int pos)
{
	return this->arr[pos];
}

void Repository::updateRepo(Dog old, Dog newdog)
{
	int pos = this->searchRepo(old.getName());
	this->arr[pos] = newdog;
	this->save();
}

void Repository::load()
{
	std::ifstream file("Dogs.txt");
	if (!file.is_open()) {
		return;
	}

	if (file.peek() == std::ifstream::traits_type::eof()) {
		this->generateDogs();
	}
	else {
	Dog d{};
	while (file >> d)
	{
		this->addRepo(d);
	}
	}
	file.close();
}

void Repository::save()
{
	std::ofstream file("Dogs.txt");
	if (!file.is_open()) {
		return;
	}
	for (auto dog : this->arr)
	{
		file << dog << std::endl;
	}
	file.close();
}

void Repository::generateDogs()
{
	Dog d1("Saint-Bernard", "Bruno", 5, "https://images.app.goo.gl/NJqT7SCz5RBCDQXX9");
	this->addRepo(d1);

	Dog d2("Husky", "Bella", 2, "https://images.app.goo.gl/tQLFozxvJgeETdhC6");
	this->addRepo(d2);

	Dog d3("Golden-Retriever", "Daisy", 1, "https://images.app.goo.gl/ZL6URyKZtSd3NGzd7");
	this->addRepo(d3);

	Dog d4("Bulldog", "Cooper", 3, "https://images.app.goo.gl/ZL6URyKZtSd3NGzd7");
	this->addRepo(d4);

	Dog d5("Poodle", "Apollo", 7, "https://images.app.goo.gl/si6RgTxBnJX15dHi9");
	this->addRepo(d5);

	Dog d6("German-Shepherd", "Lola", 4, "https://images.app.goo.gl/cSTpU3HYBeidPCqU6");
	this->addRepo(d6);

	Dog d7("Doberman", "Kyra", 5, "https://images.app.goo.gl/JMZjaprv61sT6vVE9");
	this->addRepo(d7);

	Dog d8("Cane - Corso", "Tucker", 8, "https://images.app.goo.gl/4wVG5c6xX4nyyWeAA");
	this->addRepo(d8);

	Dog d9("Corgi", "Ollie", 1, "https://images.app.goo.gl/vnT4s1XemoC8zV8e7");
	this->addRepo(d9);

	Dog d10("Saint-Bernard", "Jack", 4, "https://images.app.goo.gl/fC7XXaM5zzkKFfTJA");
	this->addRepo(d10);

}

bool Repository::addRepo(Dog d)
{
	for (auto dog : this->arr)
	{
		if (dog.getName() == d.getName())
			throw ValidationException("Dog already in the shelter");
	}

	this->arr.push_back(d);
	this->save();
	return true;
}