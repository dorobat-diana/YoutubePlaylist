#include <fstream>
#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(Controller *newcontroller,FileTutorialList* tutoriallist1, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::UserWindow) {
     //ctrl =Controller (tutoriallist);
    controller = newcontroller;
    tutoriallist=tutoriallist1;
    readfromfile();
    ui->setupUi(this);
    getnexttutorial();
    connect(ui->NextButton, SIGNAL(clicked()), this, SLOT(getnexttutorial()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(ui->AddButton, SIGNAL(clicked()), this, SLOT(addtowatch()));
    connect(ui->NextButton_2, SIGNAL(clicked()), this, SLOT(getnexttutorialwatch()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    connect(ui->LikeButton, SIGNAL(clicked()),this,SLOT(like()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(backbuttonclicked()));
    connect(ui->display,SIGNAL(clicked()),this,SLOT(display()));
}

UserWindow::~UserWindow() {
    delete ui;
}

void UserWindow::backbuttonclicked() {
    this->hide();
    emit userback();
}

void UserWindow::getnexttutorial() {
    this->ui->tutorialuserlist->clear();
    int size;
    if (presenter == "") {
        size = controller->getAllTutorials().size();
        index = (index + 1) % size;
        Tutorial currentTutorial = controller->getAllTutorials()[index];
        QString itemInList = QString::fromStdString(
                currentTutorial.getTitle() + " - " + currentTutorial.getPresenter() + " - " +
                to_string(currentTutorial.getDurationMinutes()) + " - " +
                to_string(currentTutorial.getDurationSeconds()) + " - " +
                to_string(currentTutorial.getLikes()) + " - " + currentTutorial.getLink());
        this->ui->tutorialuserlist->addItem(itemInList);

    } else {
        size = controller->getTutorialsByPresenter(presenter).size();
        index_presenter = (index + 1) % size;
        Tutorial currentTutorial = controller->getTutorialsByPresenter(presenter)[index];
        QString itemInList = QString::fromStdString(
                currentTutorial.getTitle() + " - " + currentTutorial.getPresenter() + " - " +
                to_string(currentTutorial.getDurationMinutes()) + " - " +
                to_string(currentTutorial.getDurationSeconds()) + " - " +
                to_string(currentTutorial.getLikes()) + " - " + currentTutorial.getLink());
        this->ui->tutorialuserlist->addItem(itemInList);
    }

}

void UserWindow::readfromfile() {
    ifstream file("../tutorials.txt");
    if (!file.is_open())
        printf("Error opening file: %s\n", strerror(errno));
    Tutorial tutorial;
    while (file >> tutorial) {
       try {
           controller->addTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                                   tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink());
       }
       catch (exception& e) {
       }
    }
    file.close();
}

void UserWindow::getbypresenter() {
    presenter = this->ui->presenter->toPlainText().toStdString();
}

void UserWindow::search() {
    index_presenter = -1;
    getbypresenter();
    getnexttutorial();
}

void UserWindow::addtowatch() {
    int selectedindex;
    Tutorial tutorial;
    if (presenter == "") {
        selectedindex = (index) % controller->getAllTutorials().size();
        tutorial = controller->getAllTutorials()[selectedindex];
    } else {
        selectedindex = (index_presenter) % controller->getTutorialsByPresenter(presenter).size();
        tutorial = controller->getTutorialsByPresenter(presenter)[selectedindex];
    }
    watch.addTutorial(tutorial);
    ctrl.addTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                      tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink());
    getnexttutorialwatch();
}

void UserWindow::getnexttutorialwatch() {
    this->ui->watchlistList->clear();
    int size;
    size = watch.getLength();
    index_watch = (index_watch + 1) % size;
    Tutorial currentTutorial = watch[index_watch];
    QString itemInList = QString::fromStdString(
            currentTutorial.getTitle() + " - " + currentTutorial.getPresenter() + " - " +
            to_string(currentTutorial.getDurationMinutes()) + " - " +
            to_string(currentTutorial.getDurationSeconds()) + " - " +
            to_string(currentTutorial.getLikes()) + " - " + currentTutorial.getLink());
    this->ui->watchlistList->addItem(itemInList);

}

void UserWindow::remove() {
    Tutorial currentTutorial = watch[index_watch];
    watch.removeTutorial(currentTutorial);
    getnexttutorialwatch();
}

void UserWindow::like() {
    Tutorial currentTutorial = watch[index_watch];
    controller->updateTutorial(currentTutorial.getTitle(), currentTutorial.getPresenter(),
                               currentTutorial.getDurationMinutes(), currentTutorial.getDurationSeconds(),
                               currentTutorial.getLikes(),currentTutorial.getLink(), currentTutorial.getTitle(), currentTutorial.getLikes() + 1,
                               currentTutorial.getLink());
    watch.updateTutorial(currentTutorial, currentTutorial.getTitle(), currentTutorial.getLikes() + 1,
                         currentTutorial.getLink());
    index--;
    index_watch--;
    getnexttutorialwatch();
    getnexttutorial();

}

void UserWindow::display(){

    ctrl.saveTutorialListToFile(tutoriallist->getFilename());
    ctrl.openTutorialListInApp();
    //this->controller->openTutorialListInApp();
}