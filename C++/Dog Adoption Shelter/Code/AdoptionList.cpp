#include "AdoptionList.h"
#include <fstream>
void AdoptionListHTML::save()
{
	std::ofstream file(this->fileName);

	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "<title>Adoption List</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border=\"1\">\n";
	file << "<tr>\n";
	file << "<td>Name</td>\n";
	file << "<td>Breed</td>\n";
	file << "<td>Age</td>\n";
	file << "<td>Link</td>\n";
	file << "</tr>\n";

	for (const auto& dog : this->dogs)
	{
		file << "<tr>\n";
		file << "<td>" << dog.getName() << "</td>\n";
		file << "<td>" << dog.getBreed() << "</td>\n";
		file << "<td>" << dog.getAge() << "</td>\n";
		file << "<td><a href=\"" << dog.getLink() << "\">Link</a></td>\n";
		file << "</tr>\n";
	}

	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";

	file.close();
}

AdoptionListHTML::AdoptionListHTML(std::string filename)
{
	this->fileName = filename;
}

void AdoptionListCSV::save()
{
	std::ofstream file(this->fileName);
	for (const auto& dog : this->dogs)
	{
		file << dog.getName() << "," << dog.getBreed() << "," << dog.getAge() << "," << dog.getLink() << "\n";
	}
	file.close();
}

AdoptionListCSV::AdoptionListCSV(std::string filename)
{
	this->fileName = filename;
}
