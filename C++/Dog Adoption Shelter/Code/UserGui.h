#pragma once  
#include <qwidget.h>  
#include "UserService.h"  
#include <qlistwidget.h>  
#include <qlineedit.h>  
#include <qpushbutton.h>  
#include <qmessagebox.h>  
#include <qlabel.h>  
#include <qpixmap.h>  
#include <qurl.h>  
#include "Chart.h"
#include <qcheckbox.h>
#include "DogsModel.h"
#include <qtableview.h>
#include <qradiobutton.h>
class UserGui : public QWidget  
{
	Q_OBJECT
private:  

UserService* userserv;  
QPushButton* seeDogsButton;  
QPushButton* seeAdoptionListButton;  
QPushButton* searchBreed;  
QPushButton* exitButton;  
QPushButton* chartButton;   
//QCheckBox* csvBox;
//QCheckBox* htmlBox;
QRadioButton* csvRadioButton;
QRadioButton* htmlRadioButton;
QPushButton* seeAdoptionListTableViewButton;
DogsModel* model;			
QTableView* adoptionListView;

public:  
UserGui(QWidget* parent = nullptr, UserService* userserv = nullptr);  
void initGui();  
void seeDogsButtonHandler();  
void seeAdoptionListButtonHandler();  
void searchBreedHandler();  
void exitButtonHandler();  
void chartButtonHandler();  
void connectSignalsAndSLots();
void adoptionListHandler(int type);
void tableViewButtonHandler();
};
