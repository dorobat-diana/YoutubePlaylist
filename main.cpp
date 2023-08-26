//
// Created by DIANA on 3/31/2023.
//

#include "main.h"
#include <vector>
#include "Tutorial.h"
#include <iostream>
#include <cassert>
#include <QApplication>
#include <QPushButton>
#include "GUI.h"
#include "GUI2.h"
#include <memory>
using namespace std;
int main(int argc,char *argv[]){
    QApplication a(argc, argv);
    Controller ctr(nullptr);
    //GUI w(ctr);
    //w.show();
    Controller somecontroller= Controller(nullptr);
    GUI2 w(&somecontroller);
    w.show();
    return a.exec();
}