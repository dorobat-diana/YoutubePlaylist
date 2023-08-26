#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "controller.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(Controller* newcontroller, QWidget *parent = nullptr);
    ~AdminWindow();

public slots:
    void add_admin();
    void delete_admin();
    void update_admin();
    void savetofile();
    void display();
    void gettutorial();
    int getSelectedIndex() const;
    void backbuttonclicked();

private:
    Ui::AdminWindow *ui;
    Controller* controller= nullptr;
    void populateList();

};

#endif // ADMINWINDOW_H
