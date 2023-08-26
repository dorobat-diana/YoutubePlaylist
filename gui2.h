//
// Created by DIANA on 5/27/2023.
//

#ifndef A45_DOROBAT_DIANA_GUI2_H
#define A45_DOROBAT_DIANA_GUI2_H

#include <QWidget>
#include "csv.h"
#include "controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI2; }
QT_END_NAMESPACE

class GUI2 : public QWidget {
Q_OBJECT

public:
    explicit GUI2(Controller *newcontroller ,QWidget *parent = nullptr);

    ~GUI2() override;
public slots:
    void on_csvMenuBackSignal();
private slots:
    void oncsvButton_clicked();
    void onhtml_Button_clicked();
private:
    Ui::GUI2 *ui;
    Controller* controller= nullptr;
    FileTutorialList* tutorialList1= nullptr;
};


#endif //A45_DOROBAT_DIANA_GUI2_H
