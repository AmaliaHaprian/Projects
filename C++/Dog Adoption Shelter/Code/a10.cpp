#include "a10.h"
#include <qlabel.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "AdminGui.h"
#include <qheaderview.h>

a10::a10(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->initGUI();

    QObject::connect(this->adminButton, &QPushButton::clicked, this, &a10::adminButtonHandler);
    QObject::connect(this->userButton, &QPushButton::clicked, this, &a10::userButtonHandler);
    QObject::connect(this->exitButton, &QPushButton::clicked, this, &a10::close);
}

a10::~a10()
{}
void a10::initGUI()
{
    //this->mainWindow = new QMainWindow{};
    //this->mainWindow->setWindowTitle("Main Window");
    //this->mainWindow->resize(800, 600);
    //this->mainWindow->show();

    this->central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);
    this->central->setStyleSheet("background-color: #fadbd8;"); // Set background color
    QLabel* welcomeLabel = new QLabel{ "WELCOME TO THE DOG SHELTER" };
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomeLabel);

    QLabel* modeLabel = new QLabel{ "Choose Mode" };
    modeLabel->setStyleSheet("font-size: 18px;");
    modeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(modeLabel);

    QVBoxLayout* buttonLayout = new QVBoxLayout{};
    this->userButton = new QPushButton{ "USER" };
    this->userButton->setStyleSheet("background-color: white; font-size: 16px;");
    this->adminButton = new QPushButton{ "ADMIN" };
    this->adminButton->setStyleSheet("background-color: white; font-size: 16px;");
    this->exitButton = new QPushButton{ "EXIT" };
    this->exitButton->setStyleSheet("background-color: white; font-size: 16px;");
    QHBoxLayout* modeButtonlayout = new QHBoxLayout{};
    modeButtonlayout->addWidget(this->userButton);
    modeButtonlayout->addWidget(this->adminButton);

    buttonLayout->addLayout(modeButtonlayout);
    buttonLayout->addWidget(this->exitButton);
    //buttonLayout->setAlignment(Qt::AlignCenter);

    //layout->addLayout(modeButtonlayout);
    layout->addLayout(buttonLayout);
    this->setCentralWidget(central);
}

void a10::adminButtonHandler()
{
    this->repo = new Repository;
    this->serv = new Service(this->repo);
    this->adminGui = new AdminGui(nullptr, this->serv);
    //QObject::connect(this->adminButton, &QPushButton::clicked, adminGui, [=]() {
    adminGui->show();
    // this->close();
    //}
    //);
}

void a10::userButtonHandler()
{
    this->repo = new Repository;
    AdoptionList* adList = new AdoptionList{};
    UserService* userserv = new UserService(this->repo, adList);
    this->userGui = new UserGui(nullptr, userserv);
    userGui->show();
    //this->close();
}