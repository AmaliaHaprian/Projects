#include "AdminGui.h"
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <string>
#include <qdialog.h>
#include "ValidationException.h"
#include <QMessageBox>
#include <exception>
#include <qtextedit.h>
int AdminGui::getSelectedItem()
{
	if (this->dogsListW->count() == 0)
		return -1;

	QModelIndexList index = this->dogsListW->selectionModel()->selectedIndexes();
	if (index.size() == 0) {
		this->nameEdit->clear();
		this->breedEdit->clear();
		this->ageEdit->clear();
		this->LinkEdit->clear();
		return -1;
	}
	int idx = index.at(0).row();
	return idx;
}

void AdminGui::listItemChanged()
{
	int idx = this->getSelectedItem();
	if (idx == -1)
		return;

	if (idx >= this->serv->getDogs().size())
		return;
	Dog dog = this->serv->getDogs()[idx];
	this->nameEdit->setText(QString::fromStdString(dog.getName()));
	this->breedEdit->setText(QString::fromStdString(dog.getBreed()));
	this->ageEdit->setText(QString::number(dog.getAge()));
	this->LinkEdit->setText(QString::fromStdString(dog.getLink()));
}

void AdminGui::connectSignalsAndSlots()
{
	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGui::addButtonHandler);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGui::deleteButtonHandler);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGui::updateButtonHandler);
	QObject::connect(this->exitButton, &QPushButton::clicked, this, &AdminGui::exitButtonHandler);

	QObject::connect(this->dogsListW, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemChanged(); });

	QObject::connect(this, &AdminGui::dogsUpdatedSignal, this, &AdminGui::populateList);

	QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGui::undoButtonHandler);
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGui::redoButtonHandler);

	QObject::connect(this, SIGNAL(addDogSignal(std::string, std::string, int, std::string)), this, SLOT(addDog(std::string, std::string, int, std::string)));

	QObject::connect(this->undoShortCut, &QShortcut::activated, this, &AdminGui::undoButtonHandler);
	QObject::connect(this->redoShortCUt, &QShortcut::activated, this, &AdminGui::redoButtonHandler);

}

AdminGui::AdminGui(QWidget* parent, Service* serv): QWidget(parent), serv(serv)
{
	this->setWindowTitle("ADMIN PAGE");
	this->initGui();
	this->connectSignalsAndSlots();
	this->populateList();
	this->resize(600, 400);
}

void AdminGui::initGui()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	this->setStyleSheet("background-color: #fadbd8;"); // Set background color
	this->dogsListW = new QListWidget{};
	this->dogsListW->setStyleSheet("background-color: white; font-size: 14px;");
	this->dogsListW->setSelectionMode(QAbstractItemView::SingleSelection);
	mainLayout->addWidget(this->dogsListW);

	QWidget* rightSide = new QWidget{};
	QVBoxLayout* rightLayout = new QVBoxLayout{rightSide};
	
	QWidget* dogAttributes = new QWidget{};

	QFormLayout* dogAttributesLayout = new QFormLayout{ dogAttributes };
	
	this->nameEdit = new QLineEdit{};
	this->nameEdit->setStyleSheet("background-color: white; font-size: 14px;");
	this->breedEdit = new QLineEdit{};
	this->breedEdit->setStyleSheet("background-color: white; font-size: 14px;");
	this->ageEdit = new QLineEdit{};
	this->ageEdit->setStyleSheet("background-color: white; font-size: 14px;");
	this->LinkEdit = new QLineEdit{};
	this->LinkEdit->setStyleSheet("background-color: white; font-size: 14px;");

	QLabel* nameLabel = new QLabel{ "Name" };
	nameLabel->setBuddy(this->nameEdit);
	QLabel* breedLabel = new QLabel{ "Breed" };
	breedLabel->setBuddy(this->breedEdit);
	QLabel* ageLabel = new QLabel{ "Age" };
	ageLabel->setBuddy(this->ageEdit);
	QLabel* linkLabel = new QLabel{ "Link" };
	linkLabel->setBuddy(this->LinkEdit);
	dogAttributesLayout->addRow(nameLabel, this->nameEdit);
	dogAttributesLayout->addRow(breedLabel, this->breedEdit);
	dogAttributesLayout->addRow(ageLabel, this->ageEdit);
	dogAttributesLayout->addRow(linkLabel, this->LinkEdit);

	rightLayout->addWidget(dogAttributes);
	

	//QWidget* buttonsWidget = new QWidget{};
	QVBoxLayout* allButtonsLayout = new QVBoxLayout{};
	QHBoxLayout* buttonsLayout = new QHBoxLayout{};
	this->addButton = new QPushButton{ "Add" };
	this->addButton->setStyleSheet("background-color: white; font-size: 14px;");
	this->deleteButton = new QPushButton{ "Delete" };
	this->deleteButton->setStyleSheet("background-color: white; font-size: 14px;");
	this->updateButton = new QPushButton{ "Update" };
	this->updateButton->setStyleSheet("background-color: white; font-size: 14px;");
	this->exitButton = new QPushButton{ "Exit" };
	this->exitButton->setStyleSheet("background-color: white; font-size: 14px;");

	QHBoxLayout* undoRedoLayout = new QHBoxLayout{};
	allButtonsLayout->addLayout(buttonsLayout);
	allButtonsLayout->addLayout(undoRedoLayout);

	this->undoButton = new QPushButton{ "Undo" };
	this->undoButton->setStyleSheet("background-color: white; font-size: 14px;");
	this->redoButton = new QPushButton{ "Redo" };
	this->redoButton->setStyleSheet("background-color: white; font-size: 14px;");

	buttonsLayout->addWidget(this->addButton);
	buttonsLayout->addWidget(this->deleteButton);
	buttonsLayout->addWidget(this->updateButton);
	//buttonsLayout->addWidget(this->exitButton);

	undoRedoLayout->addWidget(this->undoButton);
	undoRedoLayout->addWidget(this->redoButton);

	allButtonsLayout->addWidget(this->exitButton);

	//rightLayout->addWidget(buttonsWidget);
	rightLayout->addLayout(allButtonsLayout);

	mainLayout->addWidget(this->dogsListW);
	mainLayout->addWidget(rightSide);

	this->undoShortCut = new QShortcut(QKeySequence("Ctrl+Z"), this);
	this->redoShortCUt = new QShortcut(QKeySequence("Ctrl+Y"), this);
}

void AdminGui::populateList()
{
	if (this->dogsListW->count() > 0)
		this->dogsListW->clear();
	
	std::vector<Dog> dogs = this->serv->getDogs();
	for (auto& dog : dogs) {
		std::string str = dog.getName() + " - " + dog.getBreed() + " - " + std::to_string(dog.getAge()) + " - " + dog.getLink();
		this->dogsListW->addItem(QString::fromStdString(str));
	}
	if (this->dogsListW->count() > 0) {
		this->dogsListW->setCurrentRow(0);
	}
}

void AdminGui::addButtonHandler()
{
	
	//QDialog* addPopUp = new QDialog(this);
	//addPopUp->setWindowTitle("Add New Dog");

	//QFormLayout* dogAttributesLayout = new QFormLayout{};
	//addPopUp->setLayout(dogAttributesLayout);

	//QLabel* nameLabel = new QLabel{ "Name" };
	//QLabel* breedLabel = new QLabel{ "Breed" };
	//QLabel* ageLabel = new QLabel{ "Age" };
	//QLabel* linkLabel = new QLabel{ "Link" };

	//this->nameEdit = new QLineEdit{};
	//this->breedEdit = new QLineEdit{};
	//this->ageEdit = new QLineEdit{};
	//this->LinkEdit = new QLineEdit{};

	//dogAttributesLayout->addRow(nameLabel, this->nameEdit);
	//dogAttributesLayout->addRow(breedLabel, this->breedEdit);
	//dogAttributesLayout->addRow(ageLabel, this->ageEdit);
	//dogAttributesLayout->addRow(linkLabel, this->LinkEdit);

	//QPushButton* saveButton = new QPushButton("Save");
	//dogAttributesLayout->addWidget(saveButton);

	//QObject::connect(saveButton, &QPushButton::clicked, [this, addPopUp]() {

	//	QString name = this->nameEdit->text();
	//	QString breed = this->breedEdit->text();
	//	QString age = this->ageEdit->text();
	//	QString link = this->LinkEdit->text();
	//	try {
	//		DogValidator::validateNumber(age.toStdString());
	//	}
	//	catch( ValidationException& e) {
	//	QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	//	return;
	//	}
	//	try {
	//		Dog d(breed.toStdString(), name.toStdString(), stoi(age.toStdString()), link.toStdString());
	//		DogValidator::validate(d);
	//	}
	//	catch (ValidationException& e) {
	//		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	//		return;
	//	}
		
	//	try {
	//		this->serv->addService(breed.toStdString(), name.toStdString(), stoi(age.toStdString()), link.toStdString());
	//		QMessageBox::information(this, "Success", "Dog added successfully!");
	//	}
	//	catch (ValidationException& e) {
	//		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	//		return;
	//	}
	//	addPopUp->accept();
	//	this->populateList();});
	//addPopUp->exec();
	
	QString name = this->nameEdit->text();
	QString breed = this->breedEdit->text();
	QString age = this->ageEdit->text();
	QString link = this->LinkEdit->text();

	emit addDogSignal(breed.toStdString(), name.toStdString(), stoi(age.toStdString()), link.toStdString());
}
void AdminGui::addDog(std::string breed, std::string name, int age, std::string link)
{
	try {
		DogValidator::validateNumber(std::to_string(age));
	}
	catch (ValidationException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
		return;
	}
	try {
		Dog d(breed, name, age, link);
		DogValidator::validate(d);
	}
	catch (ValidationException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
		return;
	}
	try {
		this->serv->addService(breed, name, age, link);
	}
	catch (ValidationException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
		return;
	}
	emit dogsUpdatedSignal();
}

void AdminGui::deleteButtonHandler()
{	
	//QDialog* deletePopUp = new QDialog(this);
	//deletePopUp->setWindowTitle("Remove Dog");

	//QFormLayout* dogAttributesLayout = new QFormLayout{};
	//deletePopUp->setLayout(dogAttributesLayout);

	//QLabel* nameLabel = new QLabel{ "Name" };
	//this->nameEdit = new QLineEdit{};
	//dogAttributesLayout->addRow(nameLabel, this->nameEdit);
	//QPushButton* saveButton = new QPushButton("Save");
	//dogAttributesLayout->addWidget(saveButton);

	//QObject::connect(saveButton, &QPushButton::clicked, [this, deletePopUp]()
	//	{QString name = this->nameEdit->text();
	//try {
	//	DogValidator::validateString(name.toStdString());
	//}
	//catch (ValidationException& e) {
	//	QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	//	return;
	//}
	//try {
	//	this->serv->removeService(name.toStdString());
	//	QMessageBox::information(this, "Success", "Dog removed successfully!");
	//}
	//catch (ValidationException& e) {
	//	QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	//	return;
	//}
	//deletePopUp->accept();
	//this->populateList();});
	//deletePopUp->exec();
	
	int idx = this->getSelectedItem();
	if (idx < 0 || idx >= this->serv->getDogs().size())
		return;

	try {
		this->serv->removeService(this->serv->getDogs()[idx].getName());
	}
	catch (ValidationException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
		return;
	}
	emit dogsUpdatedSignal();
}

void AdminGui::updateButtonHandler()
{	
	//QDialog* updatePopUp = new QDialog(this);
	//updatePopUp->setWindowTitle("Update Dog");

	//QFormLayout* dogAttributesLayout = new QFormLayout{};
	//updatePopUp->setLayout(dogAttributesLayout);

	//QLabel* nameLabel = new QLabel{ "Name" };
	//QLabel* breedLabel = new QLabel{ "New Breed" };
	//QLabel* ageLabel = new QLabel{ "New Age" };
	//QLabel* linkLabel = new QLabel{ "New Link" };

	//this->nameEdit = new QLineEdit{};
	//this->breedEdit = new QLineEdit{};
	//this->ageEdit = new QLineEdit{};
	//this->LinkEdit = new QLineEdit{};

	//dogAttributesLayout->addRow(nameLabel, this->nameEdit);
	//dogAttributesLayout->addRow(breedLabel, this->breedEdit);
	//dogAttributesLayout->addRow(ageLabel, this->ageEdit);
	//dogAttributesLayout->addRow(linkLabel, this->LinkEdit);

	//QPushButton* saveButton = new QPushButton("Save");
	//dogAttributesLayout->addWidget(saveButton);

	//QObject::connect(saveButton, &QPushButton::clicked, [this, updatePopUp]()
	//{
	//QString name = this->nameEdit->text();
	//QString breed = this->breedEdit->text();
	//QString age = this->ageEdit->text();
	//QString link = this->LinkEdit->text();

	//std::string std_name = name.toStdString();
	//std::string std_breed = breed.toStdString();
	//std::string std_age = age.toStdString();
	//std::string std_link = link.toStdString();

	//int cmd;
	//if (std_breed != "") {
	//	cmd = 1;
	//	try {
	//		DogValidator::validateString(std_breed);
	//	}
	//	catch (ValidationException& e) {
	//		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	//		return;
	//	}
	//	this->serv->updateService(std_name, cmd, std_breed);
	//}
	//else if (std_age != "") { cmd = 2;
	//	try {
	//		DogValidator::validateNumber(std_age);
	//	}
	//	catch (ValidationException& e) {
	//		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	//		return;
	//	}
	//	this->serv->updateService(std_name, cmd,"", stoi(std_age));
	//}
	
	//else if (std_link != "") {
	//	cmd = 3;
	//	try {
	//		DogValidator::validateString(std_link);
	//	}
	//	catch (ValidationException& e) {
	//		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	//		return;
	//	}
	//	this->serv->updateService(std_name, cmd, std_link);
	//}
	
	//updatePopUp->accept();
	//this->populateList();});
	//updatePopUp->exec();
	
	int idx = this->getSelectedItem();
	if (idx < 0 || idx >= this->serv->getDogs().size())
		return;
	QString name = this->nameEdit->text();
	QString breed = this->breedEdit->text();
	QString age = this->ageEdit->text();
	QString link = this->LinkEdit->text();

	std::string std_name = name.toStdString();
	std::string std_breed = breed.toStdString();
	std::string std_age = age.toStdString();
	std::string std_link = link.toStdString();

	int cmd = 1;
	try{
		DogValidator::validateString(std_breed);
	}
	catch (ValidationException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
		return;
	}
	this->serv->updateService(std_name, cmd, std_breed);

	cmd = 2;
	try {
		DogValidator::validateNumber(std_age);
	}
	catch (ValidationException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
		return;
	}
	this->serv->updateService(std_name, cmd, "", stoi(std_age));

	cmd = 3;
	try {
		DogValidator::validateLink(std_link);
	}
	catch (ValidationException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
		return;
	}
	this->serv->updateService(std_name, cmd, std_link);

	emit dogsUpdatedSignal();
}

void AdminGui::exitButtonHandler()
{
	this->close();
}

void AdminGui::undoButtonHandler()
{
	try{
	this->serv->undo();
	emit dogsUpdatedSignal();
	}
	catch (ValidationException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
		return;
	}
}

void AdminGui::redoButtonHandler()
{
	try{
	this->serv->redo();
	emit dogsUpdatedSignal();
	}
	catch(ValidationException& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
		return;
	}
}
