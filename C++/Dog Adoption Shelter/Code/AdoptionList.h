#pragma once
#include <string>
#include <vector>
#include "Dog.h"

class AdoptionList
{
protected:
	std::vector<Dog> dogs;
	virtual void save() {};

public:
	AdoptionList() {};
	virtual ~AdoptionList() {};
	int getSize() {
		return this->dogs.size();
	}
	void addDog(const Dog& dog) {
		this->dogs.push_back(dog);
		this->save();
	}
	Dog getDog(int index) {
		if (index < 0 || index >= this->dogs.size())
			throw std::out_of_range("Index out of range");
		return this->dogs[index];
	}
	std::vector<Dog> getDogs() {
		return this->dogs;
	}
	virtual std::string getFileName() { return ""; };
	virtual std::string getFilePath() { return ""; };
};

class AdoptionListHTML : public AdoptionList
{
private:
	std::string fileName;
	void save() override;
public:
	AdoptionListHTML(std::string filename);
	~AdoptionListHTML() override {};
	std::string getFileName() {
		return this->fileName;
	}
	std::string getFilePath() {
		return "C:\\Users\\Amalia\\source\\repos\\a9_try\\a9_try\\adoptionlist.html";
	}
};

class AdoptionListCSV : public AdoptionList
{
private:
	std::string fileName;
	void save() override;
public:
	AdoptionListCSV(std::string filename);
	~AdoptionListCSV() override {};
	std::string getFileName() {
		return this->fileName;
	}
	std::string getFilePath() {
		return "C:\\Users\\Amalia\\source\\repos\\a9_try\\a9_try\\adoptionlist.csv";
	}
};