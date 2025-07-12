#include "Chart.h"
#include <QPainter>
#include <qpen.h>
#include <map>
#include <vector>
#include <qdialog.h>

Chart::Chart(QWidget* parent, UserService* serv) : QWidget(parent), serv(serv)
{
	this->setWindowTitle("Adoption List Chart");
	this->resize(600, 400);
	this->calculateBreedCounts();
	colors = { Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta, Qt::darkGray, Qt::lightGray, Qt::black};
}

void Chart::paintEvent(QPaintEvent* event)
{
	this->setAutoFillBackground(true);
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int left = 40;
	int bottom = 320;
	int top = 50;
	int right = left + 50 * this->breeds.size();

	painter.drawLine(left,bottom,right, bottom);
	painter.drawLine(left, top, left, bottom);

    int maxBreeds = std::max_element(this->breedCounts.begin(), this->breedCounts.end(), 
       [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
           return a.second < b.second;
       })->second;
	
	int yTicks = 2;
	for (int i = 0; i <= yTicks; i++) {
		int y = bottom - (i * (bottom - top) / yTicks);
		painter.drawLine(left - 5, y, left, y);
		painter.drawText(5, y + 5, QString::number(i * maxBreeds / yTicks));
	}

	for (int i = 0;i < this->breeds.size(); i++) {
		int x = left + i * 50 + 10;
		int barHeight = (this->breedCounts[this->breeds[i].toStdString()] * (bottom-top) / maxBreeds);
		int y = bottom - barHeight;
		painter.setBrush(colors[i]);
		painter.drawRect(x, y, 30, barHeight);

		painter.save();
		painter.translate(x + 15, bottom + 20);
		painter.rotate(45);
		painter.drawText(0, 0, this->breeds[i]);
		painter.restore();
	}
	
	painter.drawText((left+right) / 2, bottom + 10, "Breeds");
	painter.drawText(left, top-10, "Counts");
}

void Chart::calculateBreedCounts()
{
	std::vector<Dog> dogs = this->serv->filterDogs("", 100);
	this->breedCounts.clear();
	this->breeds.clear();

	for (const Dog& dog : dogs) {
		this->breedCounts[dog.getBreed()]++;
	}
	for (const auto& pair : this->breedCounts) {
		this->breeds.push_back(QString::fromStdString(pair.first));
	}
}
