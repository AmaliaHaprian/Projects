#include "UserGui.h"
#include <qlabel.h>
#include <string>
#include <qdialog.h>
#include "ValidationException.h"
#include <QMessageBox>
#include <exception>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <QListWidget>
#include <QPainter>
#include <map>
#include <vector>
#include <qstring.h>
#include <qurl.h>
#include <qdebug.h>
#include <QImageReader> 
#include <qbuttongroup.h>
#include <qdesktopservices.h>
#include <qfileinfo.h>
#include <qtableview.h>
#include <qheaderview.h>

UserGui::UserGui(QWidget* parent, UserService* userserv) : QWidget(parent), userserv(userserv)
{
	this->setWindowTitle("USER PAGE");
	this->initGui();
	this->resize(600, 400);
	QObject::connect(this->seeDogsButton, &QPushButton::clicked, this, &UserGui::seeDogsButtonHandler);
	QObject::connect(this->seeAdoptionListButton, &QPushButton::clicked, this, &UserGui::seeAdoptionListButtonHandler);
	QObject::connect(this->searchBreed, &QPushButton::clicked, this, &UserGui::searchBreedHandler);
	QObject::connect(this->exitButton, &QPushButton::clicked, this, &UserGui::exitButtonHandler);
	QObject::connect(this->chartButton, &QPushButton::clicked, this, &UserGui::chartButtonHandler);

	QObject::connect(this->seeAdoptionListTableViewButton, &QPushButton::clicked, this, &UserGui::tableViewButtonHandler);

	this->connectSignalsAndSLots();
}

void UserGui::initGui()
{
	QVBoxLayout* mainLayout = new QVBoxLayout{ this };
	this->setStyleSheet("background-color: #fadbd8;");

	QHBoxLayout* checkBoxLayout = new QHBoxLayout{};
	QLabel* checkLabel = new QLabel{ "Choose the format of the adoption list:" };
	//this->csvBox = new QCheckBox("CSV File");
	//this->htmlBox = new QCheckBox("HTML File");
	this->csvRadioButton = new QRadioButton("CSV File");
	this->htmlRadioButton = new QRadioButton("HTML File");
	checkBoxLayout->addWidget(checkLabel);
	checkBoxLayout->addWidget(this->csvRadioButton);
	checkBoxLayout->addWidget(this->htmlRadioButton);
	mainLayout->addLayout(checkBoxLayout);

	//QButtonGroup* group = new QButtonGroup(this);
	//group->setExclusive(true);
	//group->addButton(this->csvRadioButton);
	//group->addButton(this->htmlRadioButton);

	this->seeDogsButton = new QPushButton{ "See Dogs" };
	this->seeDogsButton->setStyleSheet("background-color: white; font-size: 16px;");
	this->seeDogsButton->setEnabled(false);

	this->seeAdoptionListButton = new QPushButton{ "See Adoption List" };
	this->seeAdoptionListButton->setEnabled(false);
	this->seeAdoptionListButton->setStyleSheet("background-color: white; font-size: 16px;");
	
	this->searchBreed = new QPushButton{ "Search Breed" };
	this->searchBreed->setEnabled(false);
	this->searchBreed->setStyleSheet("background-color: white; font-size: 16px;");
	this->chartButton = new QPushButton{ "See Chart" };

	this->chartButton->setStyleSheet("background-color: white; font-size: 16px;");
	this->exitButton = new QPushButton{ "Exit" };
	this->exitButton->setStyleSheet("background-color: white; font-size: 16px;");

	this->seeAdoptionListTableViewButton = new QPushButton{ "See table" };
	this->seeAdoptionListTableViewButton->setStyleSheet("background-color: white; font-size: 16px;");

	mainLayout->addWidget(this->seeDogsButton);
	mainLayout->addWidget(this->seeAdoptionListButton);
	mainLayout->addWidget(this->searchBreed);
	mainLayout->addWidget(this->chartButton);
	mainLayout->addWidget(this->seeAdoptionListTableViewButton);
	mainLayout->addWidget(this->exitButton);
	

	//this->model = model;
	//this->adoptionListView = new QTableView(this);
	//this->adoptionListView->setModel(this->model);
	//this->adoptionListView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	this->setLayout(mainLayout);
}

void UserGui::seeDogsButtonHandler()
{	
	std::vector<Dog> dogs = this->userserv->filterDogs("", 100);
	std::vector<std::string> image_paths = this->userserv->image_paths();
	if (dogs.empty()) {
		QMessageBox::information(this, "Info", "No dogs available.");
		return;
	}

	QDialog* dogDialog = new QDialog(this);
	dogDialog->setWindowTitle("See Dogs");
	QVBoxLayout* layout = new QVBoxLayout(dogDialog);

	QLabel* infoLabel = new QLabel;
	QLabel* imageLabel = new QLabel;
	imageLabel->setFixedSize(250, 250);
	imageLabel->setAlignment(Qt::AlignCenter);

	QPushButton* nextButton = new QPushButton("Next");
	QPushButton* adoptButton = new QPushButton("Adopt");
	QPushButton* closeButton = new QPushButton("Close");

	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(adoptButton);
	buttonLayout->addWidget(nextButton);
	buttonLayout->addWidget(closeButton);

	layout->addWidget(infoLabel);
	layout->addWidget(imageLabel);
	layout->addLayout(buttonLayout);

	int* currentIndex = new int(0);

	auto updateDog = [=]() {
		const Dog& dog = dogs[*currentIndex];
		QString info = QString::fromStdString(
			dog.getName() + " - " + dog.getBreed() + " - " +
			std::to_string(dog.getAge()) + " years"
		);
		infoLabel->setText(info);
		qDebug() << QImageReader::supportedImageFormats();
		QPixmap pixmap;
		if (pixmap.load(QString::fromStdString(image_paths.at(*currentIndex))))
			imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio));
		else
			imageLabel->setText("Image not found");
		};

	updateDog();

	QObject::connect(nextButton, &QPushButton::clicked, [=]() {
		*currentIndex = (*currentIndex + 1) % dogs.size();
		updateDog();
		});

	QObject::connect(adoptButton, &QPushButton::clicked, [=]() {
		//this->userserv->addToList(dogs[*currentIndex]);
		this->model->addDog(dogs[*currentIndex]);
		if (dogs.empty()) {
			dogDialog->accept();
			return;
		}
		if (*currentIndex >= dogs.size()) *currentIndex = 0;
		updateDog();
		});

	QObject::connect(closeButton, &QPushButton::clicked, dogDialog, &QDialog::accept);

	dogDialog->exec();
	delete currentIndex;
	
	/*
	std::vector<Dog> dogs = this->userserv->filterDogs("", 100);
	if (dogs.empty()) {
		QMessageBox::information(this, "Info", "No dogs available.");
		return;
	}

	QDialog* dogDialog = new QDialog(this);
	dogDialog->setWindowTitle("See Dogs");
	QVBoxLayout* layout = new QVBoxLayout(dogDialog);

	QLabel* infoLabel = new QLabel;
	QLabel* imageLabel = new QLabel;
	imageLabel->setFixedSize(250, 250);
	imageLabel->setAlignment(Qt::AlignCenter);

	QPushButton* nextButton = new QPushButton("Next");
	QPushButton* adoptButton = new QPushButton("Adopt");
	QPushButton* closeButton = new QPushButton("Close");

	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(adoptButton);
	buttonLayout->addWidget(nextButton);
	buttonLayout->addWidget(closeButton);

	layout->addWidget(infoLabel);
	layout->addWidget(imageLabel);
	layout->addLayout(buttonLayout);

	int* currentIndex = new int(0);

	auto updateDog = [=]() {
		const Dog& dog = dogs[*currentIndex];
		QString info = QString::fromStdString(
			dog.getName() + " - " + dog.getBreed() + " - " +
			std::to_string(dog.getAge()) + " years"
		);
		infoLabel->setText(info);
		std::string link = dog.getLink();
		QUrl url(QString::fromStdString(link));
		qDebug() << "Trying to load image from:" << QString::fromStdString(link);

		QNetworkRequest request(url);
		QNetworkReply* reply = this->networkManager->get(request);

		QObject::connect(reply, &QNetworkReply::finished, [=]() {
			if (reply->error() == QNetworkReply::NoError) {
				QByteArray data = reply->readAll();
				QPixmap pixmap;
				pixmap.loadFromData(data);
				imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio));
			}
			else {
				imageLabel->setText("Image not found");
			}
			reply->deleteLater();
			});
		};

	updateDog();

	QObject::connect(nextButton, &QPushButton::clicked, [=]() {
		*currentIndex = (*currentIndex + 1) % dogs.size();
		updateDog();
		});

	QObject::connect(adoptButton, &QPushButton::clicked, [=]() {
		this->userserv->addToList(dogs[*currentIndex]);
		QMessageBox::information(dogDialog, "Adopted", "Dog added to adoption list!");
		if (dogs.empty()) {
			dogDialog->accept();
			return;
		}
		if (*currentIndex >= dogs.size()) *currentIndex = 0;
		updateDog();
		});

	QObject::connect(closeButton, &QPushButton::clicked, dogDialog, &QDialog::accept);

	dogDialog->exec();
	delete currentIndex;
	*/
}

void UserGui::seeAdoptionListButtonHandler()
{
	/*
	QDialog* adoptionListPopUp = new QDialog(this);
	adoptionListPopUp->setWindowTitle("Adoption List");
	adoptionListPopUp->resize(400, 300);
	QVBoxLayout* layout = new QVBoxLayout{ adoptionListPopUp };
	QListWidget* adoptionListW = new QListWidget{};
	layout->addWidget(adoptionListW);
	std::vector<Dog> dogs = this->userserv->getAdoptionList();
	for (auto& dog : dogs) {
		std::string str = dog.getName() + " - " + dog.getBreed() + " - " + std::to_string(dog.getAge()) + " - " + dog.getLink();
		adoptionListW->addItem(QString::fromStdString(str));
	}
	adoptionListPopUp->exec();
	*/
	std::string filePath = this->userserv->getFilePath();
	QString qFilePath = QString::fromStdString(filePath);
	QUrl url = QUrl::fromLocalFile(qFilePath);
	QDesktopServices::openUrl(url);
}

void UserGui::searchBreedHandler()
{
	QDialog* searchPopUp = new QDialog(this);
	
	searchPopUp->setWindowTitle("Search Breed");
	QFormLayout* layout = new QFormLayout{ searchPopUp };
	QLabel* breedLabel = new QLabel{ "Breed" };
	QLabel* ageLabel = new QLabel{ "Max Age" };

	QLineEdit* breedEdit = new QLineEdit{};
	QLineEdit* ageEdit = new QLineEdit{};
	layout->addRow(breedLabel, breedEdit);
	layout->addRow(ageLabel, ageEdit);
	
	QPushButton* searchButton = new QPushButton{ "Search" };
	QPushButton* closeButton = new QPushButton{ "Close" };
	layout->addWidget(searchButton);
	layout->addWidget(closeButton);

	/*
	QListWidget* resultListW = new QListWidget{};
	layout->addWidget(resultListW);
	QObject::connect(searchButton, &QPushButton::clicked, [=]() {
		std::string breed = breedEdit->text().toStdString();
		std::string age = ageEdit->text().toStdString();
		std::vector<Dog> dogs = this->userserv->filterDogs(breed, stoi(age));
		resultListW->clear();
		for (auto& dog : dogs) {
			std::string str = dog.getName() + " - " + dog.getBreed() + " - " + std::to_string(dog.getAge()) + " - " + dog.getLink();
			resultListW->addItem(QString::fromStdString(str));
		}
		});
		*/
	QObject::connect(closeButton, &QPushButton::clicked, searchPopUp, &QDialog::accept);
	QObject::connect(searchButton, &QPushButton::clicked, [=](){
		QDialog* dogDialog = new QDialog(this);
		dogDialog->setWindowTitle("See Dogs");
		QVBoxLayout* dogsLayout = new QVBoxLayout(dogDialog);

		QLabel* infoLabel = new QLabel;
		QLabel* imageLabel = new QLabel;
		imageLabel->setFixedSize(250, 250);
		imageLabel->setAlignment(Qt::AlignCenter);

		QPushButton* nextButton = new QPushButton("Next");
		QPushButton* adoptButton = new QPushButton("Adopt");
		QPushButton* closeButton = new QPushButton("Close");

		QHBoxLayout* buttonLayout = new QHBoxLayout;
		buttonLayout->addWidget(adoptButton);
		buttonLayout->addWidget(nextButton);
		buttonLayout->addWidget(closeButton);

		dogsLayout->addWidget(infoLabel);
		dogsLayout->addWidget(imageLabel);
		dogsLayout->addLayout(buttonLayout);


		std::string breed = breedEdit->text().toStdString();
		std::string age = ageEdit->text().toStdString();
		std::vector<Dog> filteredDogs = this->userserv->filterDogs(breed, stoi(age));
		std::vector<Dog> dogs = this->userserv->filterDogs("", 100);
		std::vector<std::string> images;
		for (auto& dog : dogs) {
			for (int i = 0;i < filteredDogs.size();i++)
				if (dog.getName() == filteredDogs[i].getName())
					images.push_back(this->userserv->image_paths().at(i));
		}

		int* currentIndex = new int(0);

		auto updateDog = [=]() {
			const Dog& dog = filteredDogs[*currentIndex];
			QString info = QString::fromStdString(
				dog.getName() + " - " + dog.getBreed() + " - " +
				std::to_string(dog.getAge()) + " years"
			);
			infoLabel->setText(info);
			qDebug() << QImageReader::supportedImageFormats();
			QPixmap pixmap;
			if (pixmap.load(QString::fromStdString(images.at(*currentIndex))))
				imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio));
			else
				imageLabel->setText("Image not found");
			};

		updateDog();

		QObject::connect(nextButton, &QPushButton::clicked, [=]() {
			*currentIndex = (*currentIndex + 1) % filteredDogs.size();
			updateDog();
			});

		QObject::connect(adoptButton, &QPushButton::clicked, [=]() {
			this->userserv->addToList(filteredDogs[*currentIndex]);
			this->model->addDog(filteredDogs[*currentIndex]);
			if (filteredDogs.empty()) {
				dogDialog->accept();
				return;
			}
			if (*currentIndex >= filteredDogs.size()) *currentIndex = 0;
			updateDog();
			});

		QObject::connect(closeButton, &QPushButton::clicked, dogDialog, &QDialog::accept);

		dogDialog->exec();
		delete currentIndex;
		});
	searchPopUp->exec();
}

void UserGui::exitButtonHandler()
{
	this->close();
}

void UserGui::chartButtonHandler()
{
	Chart* chart = new Chart(this, this->userserv);
	chart->show();
}

void UserGui::connectSignalsAndSLots()
{
QObject::connect(this->csvRadioButton, &QRadioButton::clicked, this->seeDogsButton, &QPushButton::setEnabled);
QObject::connect(this->csvRadioButton, &QRadioButton::clicked, this->seeAdoptionListButton, &QPushButton::setEnabled);
QObject::connect(this->csvRadioButton, &QRadioButton::clicked, this->searchBreed, &QPushButton::setEnabled);

QObject::connect(this->htmlRadioButton, &QRadioButton::clicked, this->seeDogsButton, &QPushButton::setEnabled);
QObject::connect(this->htmlRadioButton, &QRadioButton::clicked, this->seeAdoptionListButton, &QPushButton::setEnabled);
QObject::connect(this->htmlRadioButton, &QRadioButton::clicked, this->searchBreed, &QPushButton::setEnabled);

QObject::connect(this->csvRadioButton, &QRadioButton::clicked, [this]() {
	if (this->csvRadioButton->isChecked()) {
		this->adoptionListHandler(1);
	}
});

QObject::connect(this->htmlRadioButton, &QRadioButton::clicked, [this]() {
	if (this->htmlRadioButton->isChecked()) {
		this->adoptionListHandler(2);
	}
	});
}

void UserGui::adoptionListHandler(int type)
{
	if (type == 1) {
		delete this->userserv->getList();
		AdoptionListCSV* list = new AdoptionListCSV("adoptionlist.csv");
		this->userserv->setList(list);
		this->model = new DogsModel(*list);
	}
	else {
		delete this->userserv->getList();
		AdoptionListHTML* list = new AdoptionListHTML("adoptionlist.html");
		this->userserv->setList(list);
		this->model = new DogsModel(*list);
	}
}

void UserGui::tableViewButtonHandler()
{
	if (this->userserv->getListSize() == 0)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("No animals in the adoption list"));
		return;
	}
	QDialog* dialog = new QDialog{ this };
	QVBoxLayout* layout = new QVBoxLayout(dialog);

	this->adoptionListView = new QTableView(dialog);

	this->adoptionListView->setModel(this->model);
	this->adoptionListView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	layout->addWidget(this->adoptionListView);
	dialog->setLayout(layout);
	dialog->resize(600, 400);
	dialog->exec();
}
