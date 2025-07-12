#include "DogsModel.h"
#include <string>

DogsModel::DogsModel(AdoptionList& adoptionList): adoptionList(adoptionList)
{
}

int DogsModel::rowCount(const QModelIndex& parent) const
{
	return this->adoptionList.getSize();
}

int DogsModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant DogsModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();

	Dog d = this->adoptionList.getDogs()[row];

	if (role == Qt::DisplayRole) {
		if (col == 0)
			return QString::fromStdString(d.getName());
		if(col==1)
			return QString::fromStdString(d.getBreed());
		if (col == 2)
			return QString::fromStdString(std::to_string(d.getAge()));
		if (col == 3)
			return QString::fromStdString(d.getLink());
	}

	return QVariant();
}

QVariant DogsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0)
				return "Name";
			if (section == 1)
				return "Breed";
			if (section == 2)
				return "Age";
			if (section == 3)
				return "Link";
		}
	}

	return QVariant();
}

void DogsModel::addDog(const Dog& dog)
{
	beginInsertRows(QModelIndex(), adoptionList.getSize(), adoptionList.getSize());
	adoptionList.addDog(dog);
	endInsertRows();
}
