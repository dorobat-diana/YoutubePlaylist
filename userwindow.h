
#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "controller.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(Controller *newcontroller,FileTutorialList* tutoriallist, QWidget *parent = nullptr);
    ~UserWindow();
    signals:
    void userback();
public slots:
    void getnexttutorial();
    void readfromfile();
    void getbypresenter();
    void search();
    void addtowatch();
    void getnexttutorialwatch();
    void remove();
    void like();
    void backbuttonclicked();
    void display();
private:
    Ui::UserWindow *ui;
    Controller *controller= nullptr;
    int index=-1;
    int index_presenter=-1;
    int index_watch=-1;
    string presenter="";
    Administrator watch;
    FileTutorialList* tutoriallist= nullptr;
    Controller ctrl=Controller(tutoriallist);
};

#endif // USERWINDOW_H
