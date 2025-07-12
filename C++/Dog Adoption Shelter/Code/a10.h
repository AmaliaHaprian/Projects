#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_a10.h"
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include "Repository.h"
#include "AdminGui.h"
#include "UserService.h"
#include "UserGui.h"
#include "AdoptionList.h"
#include <qtableview.h>

class a10 : public QMainWindow
{
    Q_OBJECT

public:
    a10(QWidget *parent = nullptr);
    QWidget* central;
    QPushButton* userButton;
    QPushButton* adminButton;
    QPushButton* exitButton;

    Repository* repo;
    Service* serv;
    AdminGui* adminGui;
    UserGui* userGui;

    ~a10();

private:
    Ui::a10Class ui;
    
    void initGUI();
    void adminButtonHandler();
    void userButtonHandler();
};
