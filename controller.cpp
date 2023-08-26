//
// Created by DIANA on 4/1/2023.
//

#include "controller.h"
#include "administrator.h"
#include <vector>
#include "tutorial.h"
#include <iostream>
#include <cassert>
using namespace std;
/**
 * @brief Constructor for the Controller class
 */
Controller::Controller(FileTutorialList* t) : administrator{Administrator() }, tutorialList{t} {}
/**
 * @brief Getter for the Administrator object
 * @return Administrator object
 */
Administrator Controller::getAdmin() {
    return this->administrator;
}
/**
 * @brief Adds a tutorial to the repository
 * @param title - string
 * @param presenter - string
 * @param duration_minutes - int
 * @param duration_seconds - int
 * @param likes - int
 * @param link - string
 * @return true if the tutorial was added, false otherwise
 */
bool Controller::addTutorial(string title, string presenter, int duration_minutes, int duration_seconds, int likes, string link) noexcept(false){
    Tutorial tutorial{ title, presenter, duration_minutes, duration_seconds, likes, link };
    try {
        this->administrator.addTutorial(tutorial);
        this->tutorialList->addTutorial(tutorial);
    }
    catch (MyExceptionAdministrator& exception) {
        throw;
    }
    return true;
}
/**
 * @brief Removes a tutorial from the repository
 * @param title - string
 * @param presenter - string
 * @param duration_minutes - int
 * @param duration_seconds - int
 * @param likes - int
 * @param link - string
 * @return true if the tutorial was removed, false otherwise
 */
bool Controller::removeTutorial(string title, string presenter, int duration_minutes, int duration_seconds, int likes, string link) {
    Tutorial tutorial{ title, presenter, duration_minutes, duration_seconds, likes, link };
    this->tutorialList->removeTutorial(tutorial);
    return this->administrator.removeTutorial(tutorial);
}
/**
 * @brief Updates a tutorial from the repository
 * @param title - string
 * @param presenter - string
 * @param duration_minutes - int
 * @param duration_seconds - int
 * @param likes - int
 * @param link - string
 * @param new_title - string
 * @param new_likes - int
 * @param new_link - string
 * @return true if the tutorial was updated, false otherwise
 */
bool Controller::updateTutorial(string title, string presenter, int duration_minutes, int duration_seconds, int likes, string link, string new_title, int new_likes, string new_link) {
    Tutorial tutorial{ title, presenter, duration_minutes, duration_seconds, likes, link };
    this->tutorialList->updateTutorial(tutorial, new_title, new_likes, new_link);
    return this->administrator.updateTutorial(tutorial, new_title, new_likes, new_link);
}
/**
 * @brief Gets all the tutorials from the repository
 * @return std::vector<Tutorial> object
 */
std::vector<Tutorial> Controller::getAllTutorials() {
    return this->administrator.getAllTutorials();
}
/**
 * @brief Gets all the tutorials from the repository that have a given presenter
 * @param presenter - string
 * @return std::vector<Tutorial> object
 */
std::vector<Tutorial> Controller::getTutorialsByPresenter(string presenter) {

    Administrator admin = this->getAdmin();
    if(presenter==""){
        return admin.getAllTutorials();
    }
    std::vector<Tutorial> tutorials_by_presenter;
    for (int i = 0; i < admin.getLength(); i++) {
        if (admin[i].getPresenter() == presenter) {
            tutorials_by_presenter.push_back(admin[i]);
        }
    }
    return tutorials_by_presenter;
}

/**
 * @brief Saves tutorial list to a file
 * @param filename - string
 */
void Controller::saveTutorialListToFile(string filename) {
    if (this->tutorialList == nullptr)
        return;
    this->tutorialList->setFilename(filename);
    this->tutorialList->writeToFile();
}

void Controller::openTutorialListInApp() {
    if (this->tutorialList == nullptr)
        return;
    this->tutorialList->displayTutorialList();
}

void Controller::set_tutorial_list(FileTutorialList *t) {
    this->tutorialList=t;
}