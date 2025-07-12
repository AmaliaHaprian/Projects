#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qshortcut.h>

class AdminGui: public QWidget
{
	Q_OBJECT
private:

	Service* serv;

	QListWidget* dogsListW;
	QLineEdit* nameEdit;
	QLineEdit* breedEdit;
	QLineEdit* ageEdit;
	QLineEdit* LinkEdit;
	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* exitButton;

	QPushButton* undoButton;
	QPushButton* redoButton;

	QShortcut* undoShortCut;
	QShortcut* redoShortCUt;

	int getSelectedItem();
	void listItemChanged();
	void connectSignalsAndSlots();
public:
	//AdminGui(Service* serv);
	AdminGui(QWidget* parent = nullptr, Service* serv=nullptr);
	void initGui();
	void populateList();
	void addButtonHandler();
	void deleteButtonHandler();
	void updateButtonHandler();
	void exitButtonHandler();
	void undoButtonHandler();
	void redoButtonHandler();

signals:
	void dogsUpdatedSignal();
	void addDogSignal(std::string breed, std::string name, int age, std::string link);

public slots:
	void addDog(std::string breed, std::string name, int age, std::string link);
};

