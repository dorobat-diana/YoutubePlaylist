//
// Created by DIANA on 5/6/2023.
//
#include <Windows.h>
#include "HTMLTutorialList.h"
#include <fstream>
#include "administrator.h"

using namespace std;

void HTMLTutorialList::writeToFile() {
    ofstream f(this->filename);
    if (!f.is_open())
        throw MyExceptionAdministrator("The file could not be opened!");
    f << "<!DOCTYPE html>\n";
    f << "<html>\n";
    f << "<head>\n";
    f << "  <title>Tutorials</title>\n";
    f << "</head>\n";
    f << "<body>\n";
    f << "<table border=\"1\">\n";
    f << "  <tr>\n";
    f << "      <td>Title</td>\n";
    f << "      <td>Presenter</td>\n";
    f << "      <td>Duration_Minutes</td>\n";
    f << "      <td>Duration_Seconds</td>\n";
    f << "      <td>Likes</td>\n";
    f << "      <td>Link</td>\n";
    f << "  </tr>\n";
    for (auto t: this->tutorials)
        f << "  <tr>\n" << "        <td>" << t.getTitle() << "</td>\n" << "     <td>" << t.getPresenter() << "</td>\n" << "     <td>"
          << t.getDurationMinutes() << "</td>\n" << "     <td>" << t.getDurationSeconds() << "</td>\n" << "     <td>"
          << t.getLikes() << "</td>\n" << "     <td>href=\"" << t.getLink() << "\">Link</a></td>\n" << "  </tr>\n";
    f << "</table>\n";
    f << "</body>\n";
    f << "</html>\n";

    f.close();
}

void HTMLTutorialList::displayTutorialList() const {
    string aux = "C:\\Users\\DIANA\\CLionProjects\\a89-dorobat-diana\\user.html"; // if the path contains spaces, we must put it inside quotations
    //ShellExecuteA(NULL, NULL, "C:\\Program Files (x86)\\OpenOffice 4\\program\\scalc.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
    ShellExecuteA(NULL, NULL, "C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Google Chrome.lnk", aux.c_str(), NULL,
                  SW_SHOWMAXIMIZED);
}