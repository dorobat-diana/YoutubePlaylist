#include <fstream>
#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(Controller* newcontroller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    this->controller=newcontroller;
    populateList();
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(add_admin()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(delete_admin()));
    connect(ui->pushButton_10,SIGNAL(clicked()),this,SLOT(update_admin()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(savetofile()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(display()));
    connect(ui->adminlist,SIGNAL(itemSelectionChanged()),this,SLOT(gettutorial()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(backbuttonclicked()));

}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::populateList() {

    this->ui->adminlist->clear();
    ifstream file("../tutorials.txt");
    if (!file.is_open())
        printf("Error opening file: %s\n", strerror(errno));
    Tutorial tutorial;
    while (file >> tutorial) {
        controller->addTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                               tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink());
    }
    file.close();
    for (auto tutorial: controller->getAllTutorials()) {
        QString itemInList = QString::fromStdString(tutorial.getTitle() + " - " + tutorial.getPresenter() + " - " +
                                                    to_string(tutorial.getDurationMinutes()) + " - " +
                                                    to_string(tutorial.getDurationSeconds()) + " - " +
                                                    to_string(tutorial.getLikes()) + " - " + tutorial.getLink());
        this->ui->adminlist->addItem(itemInList);
    }

}

void AdminWindow::add_admin() {
    string title = this->ui->title_2->toPlainText().toStdString();
    string presenter = this->ui->presenter_2->toPlainText().toStdString();
    int minutes = this->ui->minutes_2->toPlainText().toInt();
    int seconds = this->ui->seconds_2->toPlainText().toInt();
    int likes = this->ui->likes_2->toPlainText().toInt();
    string link = this->ui->link_2->toPlainText().toStdString();
    Tutorial tutorial{title, presenter, minutes, seconds, likes, link};
    if (controller->addTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                               tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink())) {
        QString itemInList = QString::fromStdString(tutorial.getTitle() + " - " + tutorial.getPresenter() + " - " +
                                                    to_string(tutorial.getDurationMinutes()) + " - " +
                                                    to_string(tutorial.getDurationSeconds()) + " - " +
                                                    to_string(tutorial.getLikes()) + " - " + tutorial.getLink());
        this->ui->adminlist->addItem(itemInList);
    }

}

void AdminWindow::delete_admin() {
    string title = this->ui->title_2->toPlainText().toStdString();
    string presenter = this->ui->presenter_2->toPlainText().toStdString();
    int minutes = this->ui->minutes_2->toPlainText().toInt();
    int seconds = this->ui->seconds_2->toPlainText().toInt();
    int likes = this->ui->likes_2->toPlainText().toInt();
    string link = this->ui->link_2->toPlainText().toStdString();
    Tutorial tutorial{title, presenter, minutes, seconds, likes, link};
    if(controller->removeTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                                 tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink())) {
        this->ui->adminlist->clear();
        for (auto tu: controller->getAllTutorials()) {
            QString itemInList = QString::fromStdString(tu.getTitle() + " - " + tu.getPresenter() + " - " +
                                                        to_string(tu.getDurationMinutes()) + " - " +
                                                        to_string(tu.getDurationSeconds()) + " - " +
                                                        to_string(tu.getLikes()) + " - " + tu.getLink());
            this->ui->adminlist->addItem(itemInList);
        }
    }
}

void AdminWindow::update_admin() {
    string title = this->ui->title_2->toPlainText().toStdString();
    string presenter = this->ui->presenter_2->toPlainText().toStdString();
    int minutes = this->ui->minutes_2->toPlainText().toInt();
    int seconds = this->ui->seconds_2->toPlainText().toInt();
    int likes = this->ui->likes_2->toPlainText().toInt();
    string link = this->ui->link_2->toPlainText().toStdString();
    Tutorial tutorial{title, presenter, minutes, seconds, likes, link};
    string new_title= this->ui->new_title_2->toPlainText().toStdString();
    int new_likes= this->ui->new_likes_2->toPlainText().toInt();
    string new_link= this->ui->new_link_2->toPlainText().toStdString();
    if(controller->updateTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                                 tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink(),new_title,new_likes,new_link)){
        this->ui->adminlist->clear();
        for (auto tu: controller->getAllTutorials()) {
            QString itemInList = QString::fromStdString(tu.getTitle() + " - " + tu.getPresenter() + " - " +
                                                        to_string(tu.getDurationMinutes()) + " - " +
                                                        to_string(tu.getDurationSeconds()) + " - " +
                                                        to_string(tu.getLikes()) + " - " + tu.getLink());
            this->ui->adminlist->addItem(itemInList);
        }}

}

void AdminWindow::savetofile() {
    string f{};
    f="../tutorials.csv";
    this->controller->saveTutorialListToFile(f);
}

void AdminWindow::display(){
    this->controller->openTutorialListInApp();
}

void AdminWindow::gettutorial() {
    int selectedindex= this->getSelectedIndex();
    if(selectedindex<0)
        return;
    Tutorial tutorial= controller->getAllTutorials()[selectedindex];
    this->ui->title_2->setText(QString::fromStdString(tutorial.getTitle()));
    this->ui->presenter_2->setText(QString::fromStdString(tutorial.getPresenter()));
    this->ui->minutes_2->setText(QString::number(tutorial.getDurationMinutes()));
    this->ui->seconds_2->setText(QString::number(tutorial.getDurationSeconds()));
    this->ui->likes_2->setText(QString::number(tutorial.getLikes()));
    this->ui->link_2->setText(QString::fromStdString(tutorial.getLink()));
}

int AdminWindow::getSelectedIndex() const {
    if (this->ui->adminlist->count() == 0)
        return -1;

    QModelIndexList index = this->ui->adminlist->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        this->ui->title_2->clear();
        this->ui->presenter_2->clear();
        this->ui->minutes_2->clear();
        this->ui->seconds_2->clear();
        this->ui->link_2->clear();
        this->ui->likes_2->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}

void AdminWindow::backbuttonclicked() {
    this->hide();

}