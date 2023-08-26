#ifndef CSV_H
#define CSV_H

#include <QMainWindow>
#include "controller.h"
#include "userwindow.h"
#include "adminwindow.h"

namespace Ui {
class CSV;
}

class CSV : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSV(Controller* newController,FileTutorialList* tutoriallist, QWidget *parent = nullptr);
    ~CSV();
public slots:
    void on_adminMenuBackSignal();
    void on_userMenuBackSignal();
private slots:
    void on_adminMenuButtonClicked();
    void onUserMenuButtonClicked();

private:
    Ui::CSV *ui;
    Controller* controller= nullptr;
    UserWindow* userwindow=nullptr;
    AdminWindow* adminwindow=nullptr;
    FileTutorialList* tutoriallist= nullptr;

};

#endif // CSV_H
