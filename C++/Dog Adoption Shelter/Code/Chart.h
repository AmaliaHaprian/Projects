#pragma once
#include <qwidget.h>
#include "UserService.h"
#include <qvector.h>
#include <qstring.h>

class Chart : public QWidget
{
	Q_OBJECT
public:
	Chart(QWidget* parent = nullptr, UserService* serv = nullptr);
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	UserService* serv;
	QVector<QColor> colors;
	std::map<std::string, int> breedCounts;
	QVector<QString> breeds;
	void calculateBreedCounts();
};

