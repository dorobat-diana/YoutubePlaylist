//
// Created by DIANA on 5/20/2023.
//

#ifndef A45_DOROBAT_DIANA_GUI_H
#define A45_DOROBAT_DIANA_GUI_H

#include <QArgument>
#include <QWidget>
#include <qwidget.h>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMainWindow>
#include "controller.h"
#include "administrator.h"
#include "FileTutorialList.h"
#include "HTMLTutorialList.h"
#include "CSVTutorialList.h"
#include "Tutorial.h"
class GUI : public QWidget{
    Q_OBJECT
private:
    //Controller& controller;
    // graphical elements
    Controller &controller;
    QPushButton *html, *csv;
    //graphical elements for csv
    QPushButton *admin,*user;
    //graphical elements for admin

    QLineEdit *title,*presenter,*minutes,*seconds,*likes,*link;
    QLineEdit *newtitle,*newlikes,*newlink;
    QPushButton *add,*delete1,*update,*display,*save;
    QListWidget* tutorialListWidget;

    //graphical element for user
    QListWidget *tutorialsuser;
    QLineEdit *presenter2;
    QPushButton *next,*addtoplaylist, *removefromplaylist, *like, *searcbypresenter, *listinplaylist;

public:
    GUI(Controller &contr):controller{contr}{
        this->initGUI();
        this->connectSignalsAndSlots();
    }
private:
    void initGUI();
    void connectSignalsAndSlots();
    void InitCSV();
    void InitHTML();
    void InitAdminCsv();
    void populateList();
    void add_admin();
    void update_admin();
    void delete_admin();
    int getSelectedIndex() const;
    void InitAdminHTML();
    void initUser();
    void searchbypresenter1();
};
#endif //A45_DOROBAT_DIANA_GUI_H
