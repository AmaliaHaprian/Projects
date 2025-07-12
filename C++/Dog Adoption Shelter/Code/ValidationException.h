#pragma once
#include <string>
#include "Dog.h"
#include <exception>

class ValidationException
{
private:
	std::string message;
public:
	ValidationException(std::string _message);
	std::string getMessage() const;
};

class ValidationExceptionIhnerited : public std::exception {

private:
	std::string message;
public:
	ValidationExceptionIhnerited(std::string _message);
	const char* what() const noexcept override;
};

class DogValidator {
public:
	static void validate(const Dog& dog);
	static void validateString(const std::string& str);
	static void validateNumber(const std::string& number);
	static void validateLink(const std::string& link);
};


