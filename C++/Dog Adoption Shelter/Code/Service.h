#pragma once
#include "Repository.h"
#include <algorithm>
#include <Action.h>
#include <memory>
//#include <Windows.h>
#include <stack>

class Service
{
private:
	Repository* repo;
	std::stack<std::unique_ptr<Action>> undoStack;
	std::stack<std::unique_ptr<Action>> redoStack;

public:

	/*
	* Constructor for the Service class
	*/
	Service(Repository* repo);

	/*
	* Function to add a dog
	* Input: breed, name, age and link of the dog
	* Output: true if the operation was successful, false otherwise(the dog was already in the list)
	*/
	bool addService(std::string breed, std::string name, int age, std::string link);

	/*
	* Function to remove a dog
	* Input: the name of the dog to be removed
	* Output: true if the operation was successful, false otherwise(there was no such dog)
	*/
	bool removeService(std::string name);

	/*
	* Getter for the repository
	*/
	Repository getRepo();

	/*
	* Gets the size of the repository
	*/
	int getSize();

	/*
	* Gets a certain dog from the repository
	* Input: an integer, representing the position of the element in the array
	* Output: a dog object
	*/
	Dog getDog(int pos);

	/*
	* Makes a certain update to an element
	* Input: name of dog to be changes, command number, new string/ new age, depending on the command
	* OutputL true if the operation was successful, false otherwise
	*/
	bool updateService(std::string name, int command, std::string newstring = "", int newage = 0);

	/*
	* Generates 10 entries and adds them to the repository
	*/
	void generate_dogs();

	/*
	Gets the vectors of dogs
	*/
	std::vector<Dog> getDogs();

	Service& operator=(const Service& other) {
		if (this != &other) {
			this->repo = other.repo;
		}
		return *this;
	}

	void undo();
	void redo();
};
