//
// Created by DIANA on 5/6/2023.
//
#include <windows.h>
#include "CSVTutorialList.h"


#include <fstream>

#include "administrator.h"

using namespace std;

void CSVTutorialList::writeToFile() {
    ofstream f(this->filename);
    if (!f.is_open())
        throw MyExceptionAdministrator("The file could not be opened!");
    for (auto t: this->tutorials)
        f << t;
    f.close();
}

void CSVTutorialList::displayTutorialList() const {

    string aux = "C:\\Users\\DIANA\\CLionProjects\\a89-dorobat-diana\\user.csv";
    ShellExecuteA(
            NULL,
            "open",
            "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Excel.lnk",
            aux.c_str(),
            NULL,
            SW_SHOWNORMAL
    );
}