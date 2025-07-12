#pragma once
#include<vector>
#include "Dog.h"

class Repository
{
private:
	std::vector<Dog> arr;

public:
	//	/*
	//	* Creates the Repository class
	//	*/
	Repository() { this->load(); };

	/*
//	* Adds to the repository
//	* Input: a Dog instance
//	* Output: true if the operation was successful, false otherwise(the dog was already in the list)
//	*/
	bool addRepo(Dog d);

	/*
//	* Searches the repository
//	* Input: the unique name of a dog
//	* Outpus: the position of the object in the list or -1 if it doesn't exist
//	*/
	int searchRepo(std::string name);

	/*
//	* Removes from the repository
//	* Input: the name of the dog to be removed
//	* Output: true if the operation was successful, false otherwise(there was no such dog)
//	*/
	bool removeRepo(std::string name);

	/*
//	* Getter for the repository
//	* Input: -
//	* Output: a copy of the repository
//	*/
	Repository getRepo();

	/*
//	* Returns the size of the repository
//	*/
	int lengthRepo();

	/*
//	* Gets a certain dog from the repository
//	* Input: an integer, representing the position of the element in the array
//	* Output: a dog object
//	*/
	Dog getDog(int pos);

	/*
//	* Updates an element
//	* Input: the old and new object
//	* Output: -
//	*/
	void updateRepo(Dog old, Dog newdog);

	/*
	Loads the repository from a file
	*/
	void load();

	/*
	Saves the repository to a file
	*/
	void save();

	Repository& operator=(const Repository& other)
	{
		if (this != &other)
		{
			this->arr = other.arr;
		}
		return *this;
	}

	void generateDogs();
};
