//
// Created by DIANA on 5/20/2023.
//

#include <fstream>
#include "GUI.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QFormLayout>

void GUI::initGUI() {
    QWidget *window = new QWidget{this};
    //this->setCentralWidget(window);
    this->csv = new QPushButton{"CSV"};
    this->html = new QPushButton{"HTML"};
    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    mainLayout->addWidget(this->csv);
    mainLayout->addWidget(this->html);
    window->setLayout(mainLayout);
    window->show();
    //hide();
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->csv, &QPushButton::clicked, this, &GUI::InitCSV);
    QObject::connect(this->html, &QPushButton::clicked, this, &GUI::InitHTML);
}

void GUI::InitCSV() {
    QWidget *window2 = new QWidget{};
    QVBoxLayout *modemanu = new QVBoxLayout{};
    this->admin = new QPushButton{"Admin Mode"};
    this->user = new QPushButton{"User Mode"};
    modemanu->addWidget(this->admin);
    modemanu->addWidget(this->user);
    window2->setLayout(modemanu);
    window2->show();
    hide();

    QObject::connect(this->admin, &QPushButton::clicked, this, &GUI::InitAdminCsv);
    QObject::connect(this->user, &QPushButton::clicked,this,&GUI::initUser);
}

void GUI::InitAdminCsv() {
    QWidget *window4 = new QWidget{};
    QVBoxLayout *modemanu = new QVBoxLayout{};
    this->add = new QPushButton{"Add"};
    this->delete1 = new QPushButton{"Delete"};
    this->update = new QPushButton{"Update"};
    this->title = new QLineEdit{};
    this->presenter = new QLineEdit{};
    this->minutes = new QLineEdit{};
    this->seconds = new QLineEdit{};
    this->likes = new QLineEdit{};
    this->link = new QLineEdit{};
    this->newtitle= new QLineEdit{};
    this->newlikes= new QLineEdit{};
    this->newlink=new QLineEdit{};
    this->tutorialListWidget = new QListWidget{};
    this->display = new QPushButton{"Display"};
    this->save = new QPushButton{"Save"};
    QFormLayout *form = new QFormLayout{};
    form->addRow("title: ", this->title);
    form->addRow("presenter: ", this->presenter);
    form->addRow("minutes: ", this->minutes);
    form->addRow("seconds: ", this->seconds);
    form->addRow("likes: ", this->likes);
    form->addRow("link: ", this->link);
    form->addRow("new title: ",this->newtitle);
    form->addRow("new likes: ",this->newlikes);
    form->addRow("new link: ",this->newlink);

    modemanu->addWidget(this->tutorialListWidget);
    modemanu->addLayout(form);

    modemanu->addWidget(this->add);
    modemanu->addWidget(this->delete1);
    modemanu->addWidget(this->update);
    modemanu->addWidget(this->display);
    modemanu->addWidget(this->save);


    window4->setLayout(modemanu);
    window4->show();
    hide();

    string filename{};
    filename = "../tutorials.csv";

    FileTutorialList *tutorialList = new CSVTutorialList{};
    tutorialList->setFilename(filename);
    controller.set_tutorial_list(tutorialList);

    this->populateList();

    QObject::connect(this->save, &QPushButton::clicked, [&]() {
        string f{};
        f="../tutorials.csv";
        controller.saveTutorialListToFile(f);
    });
    QObject::connect(this->display, &QPushButton::clicked, [&]() {
        controller.openTutorialListInApp();
    });
    QObject::connect(this->add, &QPushButton::clicked, this, &GUI::add_admin);
    QObject::connect(this->update,&QPushButton::clicked,this,&GUI::update_admin);
    QObject::connect(this->delete1,&QPushButton::clicked,this,&GUI::delete_admin);
    QObject::connect(this->tutorialListWidget,&QListWidget::itemSelectionChanged,[this](){
        int selectedindex= this->getSelectedIndex();
        if(selectedindex<0)
            return;
        Tutorial tutorial= controller.getAllTutorials()[selectedindex];
        this->title->setText(QString::fromStdString(tutorial.getTitle()));
        this->presenter->setText(QString::fromStdString(tutorial.getPresenter()));
        this->minutes->setText(QString::number(tutorial.getDurationMinutes()));
        this->seconds->setText(QString::number(tutorial.getDurationSeconds()));
        this->likes->setText(QString::number(tutorial.getLikes()));
        this->link->setText(QString::fromStdString(tutorial.getLink()));
    });

}

int GUI::getSelectedIndex() const {
    if (this->tutorialListWidget->count() == 0)
        return -1;

    QModelIndexList index = this->tutorialListWidget->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        this->title->clear();
        this->presenter->clear();
        this->minutes->clear();
        this->seconds->clear();
        this->link->clear();
        this->likes->clear();
        return -1;
    }

    int idx = index.at(0).row();
    return idx;
}


void GUI::delete_admin() {
    string title = this->title->text().toStdString();
    string presenter = this->presenter->text().toStdString();
    int minutes = this->minutes->text().toInt();
    int seconds = this->seconds->text().toInt();
    int likes = this->likes->text().toInt();
    string link = this->link->text().toStdString();
    Tutorial tutorial{title, presenter, minutes, seconds, likes, link};
    if(controller.removeTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                                 tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink())) {
        this->tutorialListWidget->clear();
        for (auto tu: controller.getAllTutorials()) {
            QString itemInList = QString::fromStdString(tu.getTitle() + " - " + tu.getPresenter() + " - " +
                                                        to_string(tu.getDurationMinutes()) + " - " +
                                                        to_string(tu.getDurationSeconds()) + " - " +
                                                        to_string(tu.getLikes()) + " - " + tu.getLink());
            this->tutorialListWidget->addItem(itemInList);
        }
    }
}

void GUI::update_admin() {
    string title = this->title->text().toStdString();
    string presenter = this->presenter->text().toStdString();
    int minutes = this->minutes->text().toInt();
    int seconds = this->seconds->text().toInt();
    int likes = this->likes->text().toInt();
    string link = this->link->text().toStdString();
    Tutorial tutorial{title, presenter, minutes, seconds, likes, link};
    string new_title= this->newtitle->text().toStdString();
    int new_likes= this->newlikes->text().toInt();
    string new_link= this->newlink->text().toStdString();
    if(controller.updateTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                                 tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink(),new_title,new_likes,new_link)){
        this->tutorialListWidget->clear();
        for (auto tu: controller.getAllTutorials()) {
            QString itemInList = QString::fromStdString(tu.getTitle() + " - " + tu.getPresenter() + " - " +
                                                        to_string(tu.getDurationMinutes()) + " - " +
                                                        to_string(tu.getDurationSeconds()) + " - " +
                                                        to_string(tu.getLikes()) + " - " + tu.getLink());
            this->tutorialListWidget->addItem(itemInList);
    }}

}

void GUI::add_admin() {
    string title = this->title->text().toStdString();
    string presenter = this->presenter->text().toStdString();
    int minutes = this->minutes->text().toInt();
    int seconds = this->seconds->text().toInt();
    int likes = this->likes->text().toInt();
    string link = this->link->text().toStdString();
    Tutorial tutorial{title, presenter, minutes, seconds, likes, link};
    if (controller.addTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                               tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink())) {
        QString itemInList = QString::fromStdString(tutorial.getTitle() + " - " + tutorial.getPresenter() + " - " +
                                                    to_string(tutorial.getDurationMinutes()) + " - " +
                                                    to_string(tutorial.getDurationSeconds()) + " - " +
                                                    to_string(tutorial.getLikes()) + " - " + tutorial.getLink());
        this->tutorialListWidget->addItem(itemInList);
    }

}

void GUI::populateList() {

    this->tutorialListWidget->clear();
    ifstream file("../tutorials.txt");
    if (!file.is_open())
        printf("Error opening file: %s\n", strerror(errno));
    Tutorial tutorial;
    while (file >> tutorial) {
        controller.addTutorial(tutorial.getTitle(), tutorial.getPresenter(), tutorial.getDurationMinutes(),
                               tutorial.getDurationSeconds(), tutorial.getLikes(), tutorial.getLink());
    }
    file.close();
    for (auto tutorial: controller.getAllTutorials()) {
        QString itemInList = QString::fromStdString(tutorial.getTitle() + " - " + tutorial.getPresenter() + " - " +
                                                    to_string(tutorial.getDurationMinutes()) + " - " +
                                                    to_string(tutorial.getDurationSeconds()) + " - " +
                                                    to_string(tutorial.getLikes()) + " - " + tutorial.getLink());
        this->tutorialListWidget->addItem(itemInList);
    }

}

void GUI::InitHTML() {
    QWidget *window3 = new QWidget{};
    QVBoxLayout *modemanu = new QVBoxLayout{};
    this->admin = new QPushButton{"Admin Mode"};
    this->user = new QPushButton{"User Mode"};
    modemanu->addWidget(this->admin);
    modemanu->addWidget(this->user);
    window3->setLayout(modemanu);
    window3->show();
    hide();

    QObject::connect(this->admin, &QPushButton::clicked, this, &GUI::InitAdminHTML);
    QObject::connect(this->user, &QPushButton::clicked,this,&GUI::initUser);

}

void GUI::InitAdminHTML(){
    QWidget *window4 = new QWidget{};
    QVBoxLayout *modemanu = new QVBoxLayout{};
    this->add = new QPushButton{"Add"};
    this->delete1 = new QPushButton{"Delete"};
    this->update = new QPushButton{"Update"};
    this->title = new QLineEdit{};
    this->presenter = new QLineEdit{};
    this->minutes = new QLineEdit{};
    this->seconds = new QLineEdit{};
    this->likes = new QLineEdit{};
    this->link = new QLineEdit{};
    this->newtitle= new QLineEdit{};
    this->newlikes= new QLineEdit{};
    this->newlink=new QLineEdit{};
    this->tutorialListWidget = new QListWidget{};
    this->display = new QPushButton{"Display"};
    this->save = new QPushButton{"Save"};
    QFormLayout *form = new QFormLayout{};
    form->addRow("title: ", this->title);
    form->addRow("presenter: ", this->presenter);
    form->addRow("minutes: ", this->minutes);
    form->addRow("seconds: ", this->seconds);
    form->addRow("likes: ", this->likes);
    form->addRow("link: ", this->link);
    form->addRow("new title: ",this->newtitle);
    form->addRow("new likes: ",this->newlikes);
    form->addRow("new link: ",this->newlink);

    modemanu->addWidget(this->tutorialListWidget);
    modemanu->addLayout(form);

    modemanu->addWidget(this->add);
    modemanu->addWidget(this->delete1);
    modemanu->addWidget(this->update);
    modemanu->addWidget(this->display);
    modemanu->addWidget(this->save);


    window4->setLayout(modemanu);
    window4->show();
    hide();

    string filename{};
    filename = "../tutorials.HTML";

    FileTutorialList *tutorialList = new HTMLTutorialList{};
    tutorialList->setFilename(filename);
    controller.set_tutorial_list(tutorialList);

    this->populateList();

    QObject::connect(this->save, &QPushButton::clicked, [&]() {
        string f{};
        f="../tutorials.html";
        controller.saveTutorialListToFile(f);
    });
    QObject::connect(this->display, &QPushButton::clicked, [&]() {
        controller.openTutorialListInApp();
    });
    QObject::connect(this->add, &QPushButton::clicked, this, &GUI::add_admin);
    QObject::connect(this->update,&QPushButton::clicked,this,&GUI::update_admin);
    QObject::connect(this->delete1,&QPushButton::clicked,this,&GUI::delete_admin);
    QObject::connect(this->tutorialListWidget,&QListWidget::itemSelectionChanged,[this](){
        int selectedindex= this->getSelectedIndex();
        if(selectedindex<0)
            return;
        Tutorial tutorial= controller.getAllTutorials()[selectedindex];
        this->title->setText(QString::fromStdString(tutorial.getTitle()));
        this->presenter->setText(QString::fromStdString(tutorial.getPresenter()));
        this->minutes->setText(QString::number(tutorial.getDurationMinutes()));
        this->seconds->setText(QString::number(tutorial.getDurationSeconds()));
        this->likes->setText(QString::number(tutorial.getLikes()));
        this->link->setText(QString::fromStdString(tutorial.getLink()));
    });

}

void GUI::initUser() {
    QWidget *window5 = new QWidget{};
    QVBoxLayout *modemanu = new QVBoxLayout{};
    this->tutorialsuser= new QListWidget{};
    this->next= new QPushButton{"Next"};
    this->addtoplaylist= new QPushButton{"Add to PLaylist"};
    this->like= new QPushButton{"Like"};
    this->listinplaylist= new QPushButton{"List tutorials in playlist"};
    this->searcbypresenter= new QPushButton{"Search"};
    this->removefromplaylist= new QPushButton{"Remove from playlist"};
    this->presenter2= new QLineEdit{};
    QFormLayout *form= new QFormLayout{};
    form->addRow("Presenter: ",this->presenter2);

    modemanu->addWidget(this->tutorialsuser);
    modemanu->addLayout(form);
    modemanu->addWidget(this->listinplaylist);
    modemanu->addWidget(this->searcbypresenter);
    modemanu->addWidget(this->addtoplaylist);
    modemanu->addWidget(this->next);
    modemanu->addWidget(this->like);
    modemanu->addWidget(this->removefromplaylist);


    window5->setLayout(modemanu);
    window5->show();
    hide();

    QObject::connect(this->searcbypresenter, &QPushButton::clicked,this,&GUI::searchbypresenter1);
}

void GUI::searchbypresenter1() {
    this->tutorialsuser->clear();
    string presenter = this->presenter2->text().toStdString();
        for(auto tutorial: controller.getAllTutorials())
        {
            if(presenter==tutorial.getPresenter()){
                this->tutorialsuser->clear();
                QString itemInList = QString::fromStdString(tutorial.getTitle() + " - " + tutorial.getPresenter() + " - " +
                                                            to_string(tutorial.getDurationMinutes()) + " - " +
                                                            to_string(tutorial.getDurationSeconds()) + " - " +
                                                            to_string(tutorial.getLikes()) + " - " + tutorial.getLink());
                this->tutorialsuser->addItem(itemInList);
            }
        }

}
