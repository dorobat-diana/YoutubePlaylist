//
// Created by DIANA on 3/31/2023.
//

#ifndef A45_DOROBAT_DIANA_ADMINISTRATOR_H
#define A45_DOROBAT_DIANA_ADMINISTRATOR_H
#include <iostream>
using namespace std;
#include <vector>
#include "Tutorial.h"
class MyExceptionAdministrator : public std::exception
{
private:
    string message;

public:
    MyExceptionAdministrator(const string& s) : message{ s } {}

    const char* what() const throw() override {
        return this->message.c_str();
    }
};
class Administrator {

protected:
    std::vector<Tutorial> tutorials;
public:
    //constructor
    Administrator();

    //destructor
    ~Administrator();
    //adds a tutorial to the list of tutorials
    bool addTutorial(Tutorial tutorial) noexcept(false);
    //removes a tutorial from the list of tutorials
    bool removeTutorial(Tutorial tutorial);
    //updates a tutorial from the list of tutorials
    bool updateTutorial(Tutorial tutorial,string new_title ,int new_likes, string new_link);
    //get length of the list of tutorials
    int getLength();
    //operator []
    Tutorial operator[](int index);
    //get an element on position
    Tutorial getElement(int position);
    //get all the tutorials
    std::vector<Tutorial> getAllTutorials();
};
#endif //A45_DOROBAT_DIANA_ADMINISTRATOR_H
