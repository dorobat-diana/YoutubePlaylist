//
// Created by DIANA on 4/1/2023.
//

#ifndef A45_DOROBAT_DIANA_CONTROLLER_H
#define A45_DOROBAT_DIANA_CONTROLLER_H
#include "HTMLTutorialList.h"
#include "CSVTutorialList.h"
#include "administrator.h"
using namespace std;
#include "tutorial.h"
#include "administrator.h"
#include "FileTutorialList.h"
class Controller{
private:
    Administrator administrator;
    FileTutorialList* tutorialList;

public:
    //constructor
    Controller(FileTutorialList* t);
    //getter for admin
    Administrator getAdmin();
    //adds a tutorial to the repository
    bool addTutorial(string title, string presenter, int duration_minutes, int duration_seconds, int likes, string link) noexcept(false);
    //removes a tutorial from the repository
    bool removeTutorial(string title, string presenter, int duration_minutes, int duration_seconds, int likes, string link);
    //updates a tutorial from the repository
    bool updateTutorial(string title, string presenter, int duration_minutes, int duration_seconds, int likes, string link, string new_title, int new_likes, string new_link);
    //returns all the tutorials from the repository
    std::vector<Tutorial> getAllTutorials();
    //returns all the tutorials from the repository that have a given presenter
    std::vector<Tutorial> getTutorialsByPresenter(string presenter);
    //saves tutorial list to a file
    void saveTutorialListToFile(string filename);

    void openTutorialListInApp();

    void set_tutorial_list(FileTutorialList* t);
};

#endif //A45_DOROBAT_DIANA_CONTROLLER_H
