//
// Created by DIANA on 5/27/2023.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI2.h" resolved

#include <fstream>
#include "gui2.h"
#include "ui_GUI2.h"
#include "csv.h"
#include "FileTutorialList.h"
#include "CSVTutorialList.h"
#include "controller.h"

GUI2::GUI2(Controller* newcontroller,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GUI2) {
        this->controller=newcontroller;
        ui->setupUi(this);
        connect(ui->CSVButton, SIGNAL(clicked()), this, SLOT(oncsvButton_clicked()));
        connect(ui->HTMLButton,SIGNAL(clicked()),this,SLOT(onhtml_Button_clicked()));
    }

GUI2::~GUI2() {
    delete ui;
}

void GUI2::on_csvMenuBackSignal() {
    this->show();
}

void GUI2::oncsvButton_clicked() {
    string filename{};
    filename = "../tutorials.csv";
    FileTutorialList *tutorialList = new CSVTutorialList{};
     tutorialList1= new CSVTutorialList{};
    tutorialList->setFilename(filename);
    tutorialList1->setFilename("../user.csv");
    controller=new Controller(tutorialList);

    controller->set_tutorial_list(tutorialList);
    CSV* csv = new CSV(controller, this->tutorialList1);
//    connect(csv, SIGNAL(csvMenuBack()), this, SLOT(on_csvMenuBackSignal()));

    csv->show();

    this->close();
}

void GUI2::onhtml_Button_clicked() {
    string filename{};
    filename ="../tutorials.html";
    FileTutorialList *tutorialList= new HTMLTutorialList{};
    tutorialList1= new HTMLTutorialList{};
    tutorialList1->setFilename("../user.html");
    tutorialList->setFilename(filename);
    controller=new Controller(tutorialList);
    controller->set_tutorial_list(tutorialList);
    CSV* csv = new CSV(this->controller, this->tutorialList1);
    csv->show();
    this->close();


}