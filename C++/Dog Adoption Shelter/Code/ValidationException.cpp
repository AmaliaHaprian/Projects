#include "ValidationException.h"
#include <cctype>
#include <algorithm>

ValidationException::ValidationException(std::string _message)
{
	this->message = _message;
}

std::string ValidationException::getMessage() const
{
	return this->message;
}

ValidationExceptionIhnerited::ValidationExceptionIhnerited(std::string _message)
{
	this->message = _message;
}

const char* ValidationExceptionIhnerited::what() const noexcept
{
	return message.c_str();
}

void DogValidator::validate(const Dog& dog)
{
	std::string error;

	std::string name = dog.getName();
	std::string breed = dog.getBreed();
	if (std::any_of(name.begin(), name.end(), ::isspace))
		error += "Name cannot contain spaces!\n";
	if (name == "")
		error += "Name cannot be empty!\n";
	if (std::find_if(name.begin(), name.end(), ::isdigit) != name.end())
		error += "Name cannot contain digits!\n";

	if (breed == "")
		error += "Breed cannot be empty!\n";
	if (std::find_if(breed.begin(), breed.end(), ::isdigit) != breed.end())
		error += "Breed cannot contain digits!\n";
	if (std::find_if(breed.begin(), breed.end(), ::isalpha) == breed.end())
	{
		error += "Breed must containt only letters!\n";
	}
	if (dog.getAge() < 0)
		error += "Age cannot be negative!\n";
	std::string link = dog.getLink();
	if (link == "")
		error += "Link cannot be empty!\n";
	if (std::find_if(link.begin(), link.end(), ::isalpha) == link.end())
	{
		error += "Link must containt letters!\n";
	}
	//if (dog.getLink().find("http://") == std::string::npos && dog.getLink().find("https://") == std::string::npos)
	//	error += "Link must start with http:// or https://\n";
	if (error.size() > 0)
		throw ValidationException(error);
}

void DogValidator::validateString(const std::string& str)
{
	if (str.empty())
		throw ValidationException("String cannot be empty!");
	if (std::any_of(str.begin(), str.end(), ::isdigit))
		throw ValidationException("String cannot contain digits!");
	if (std::find_if(str.begin(), str.end(), ::isalpha) == str.end())
		throw ValidationException("String must contain letters!");
	//if (std::any_of(str.begin(), str.end(), ::isspace))
	//	throw ValidationException("String cannot contain spaces!");
}

void DogValidator::validateNumber(const std::string& number)
{
	if (number.empty())
		throw ValidationException("Age cannot be empty!");
	if (std::find_if(number.begin(), number.end(), ::isalpha) != number.end())
		throw ValidationException("Age cannot contain letters!");
	if (std::find_if(number.begin(), number.end(), ::isspace) != number.end())
		throw ValidationException("Age cannot contain spaces!");
	if (stoi(number) < 0)
		throw ValidationException("Age cannot be negative!");
}

void DogValidator::validateLink(const std::string& link)
{
	if (link.empty())
		throw ValidationException("Link cannot be empty!");
	if (std::find_if(link.begin(), link.end(), ::isalpha) == link.end())
		throw ValidationException("Link must contain letters!");
	//if (link.find("http://") == std::string::npos && link.find("https://") == std::string::npos)
	//	throw ValidationException("Link must start with http:// or https://");
}
