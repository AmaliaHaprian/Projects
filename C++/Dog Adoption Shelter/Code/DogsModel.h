#pragma once
#include <qabstractitemmodel.h>
#include "AdoptionList.h"

class DogsModel: public QAbstractTableModel
{
	Q_OBJECT
private:
	AdoptionList& adoptionList;
public:
	DogsModel(AdoptionList& adoptionList);
	
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void addDog(const Dog& dog);

};

