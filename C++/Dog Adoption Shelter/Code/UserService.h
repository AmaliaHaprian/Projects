#pragma once
#include "Repository.h"
#include "Dog.h"
#include <string>
#include "AdoptionList.h"

class UserService
{
private:
	Repository* repo;
	//std::vector<Dog> adoptionList;
	AdoptionList* adoptionList;

public:
	UserService(Repository* repo, AdoptionList* adList );
	bool addToList(Dog d);
	std::vector<Dog> getAdoptionList();
	std::vector<Dog> filterDogs(std::string breed, int age);
	std::vector<std::string> image_paths();
	AdoptionList* getList();
	void setList(AdoptionList* newList);
	~UserService() {
		// Destructor
	};
	int getListSize() {
		return this->adoptionList->getSize();
	}

	UserService& operator=(const UserService& other) {
		if (this != &other) {
			this->repo = other.repo;
			this->adoptionList = other.adoptionList;
		}
		return *this;
	}

	std::string getAdoptionListFileName() {
		return this->adoptionList->getFileName();
	}
	std::string getFilePath() {
		return this->adoptionList->getFilePath();
	}
};
