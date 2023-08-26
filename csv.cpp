#include "csv.h"
#include "ui_csv.h"
#include "adminwindow.h"
#include "userwindow.h"

CSV::CSV(Controller* newController,FileTutorialList* file1, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSV)
{
    this->tutoriallist=file1;
    this->controller= newController;
    adminwindow= new AdminWindow(this->controller);
    userwindow= new UserWindow(this->controller,this->tutoriallist);
    ui->setupUi(this);
    connect(ui->adminButton, SIGNAL(clicked()), this, SLOT(on_adminMenuButtonClicked()));
    connect(ui->userButton, SIGNAL(clicked()),this,SLOT(onUserMenuButtonClicked()));
    //connect(SIGNAL(userback()),this,SLOT(on_userMenuBackClicked()));

}


CSV::~CSV()
{
    delete ui;
}

void CSV::on_adminMenuButtonClicked() {

    //connect(adminwindow,  SIGNAL(adminMenuBack()),this, SLOT(on_adminMenuBackSignal()));
    adminwindow->show();
    //this->close();


}

void CSV::on_adminMenuBackSignal() {
    this->show();
}

void CSV::on_userMenuBackSignal(){
    this->show();
}

void CSV::onUserMenuButtonClicked() {

    userwindow->show();
    //this->close();
}
