//
// Created by DIANA on 3/31/2023.
//

#include "administrator.h"
#include <iostream>
using namespace std;
#include <vector>
#include "Tutorial.h"

/**
 * Default constructor
 * @param _tutorials
 */
Administrator::Administrator(): tutorials(std::vector<Tutorial>())  {}
/**
 * Copy constructor
 * @param _tutorials
 */
Administrator::~Administrator() {}
/**
 * Copy constructor
 * @param _tutorials
 */
bool Administrator::addTutorial(Tutorial tutorial) noexcept(false){
    for(int i=0;i<this->tutorials.size(); i++){
        if(this->tutorials[i] == tutorial){
            throw MyExceptionAdministrator{"Tutorial already exists!\n"};

        }
    }
    int initial_size=this->tutorials.size();
     this->tutorials.push_back(tutorial);
     if (this->tutorials.size() == initial_size + 1){
         return true;
     }
     throw MyExceptionAdministrator{"Tutorial could not be added!"};

}
/**
 * Copy constructor
 * @param _tutorials
 */
bool Administrator::removeTutorial(Tutorial tutorial) {
    int pos=-1;
    for(int i=0;i<this->tutorials.size(); i++){
        if(this->tutorials[i] == tutorial){
            pos=i;
        }
    }
    if(pos==-1){
        throw MyExceptionAdministrator{"Tutorial does not exist!"};
    }
    else{
        this->tutorials.erase(this->tutorials.begin() + pos);
        return true;
    }
}
/**
 * Copy constructor
 * @param _tutorials
 */
bool Administrator::updateTutorial(Tutorial tutorial, string new_title, int new_likes, string new_link) {
    if(new_title=="" || new_likes<0 || new_link=="" || new_link.find("www")!=0)
        throw MyExceptionAdministrator{"Invalid data!"};
    for(auto & _tutorial : this->tutorials){
        if(_tutorial==tutorial){
            _tutorial.setTitle(new_title);
            _tutorial.setLikes(new_likes);
            _tutorial.setLink(new_link);
            return true;
        }
    }
    throw MyExceptionAdministrator{"Tutorial does not exist!"};
}
/**
 * Copy constructor
 * @param _tutorials
 */
int Administrator::getLength() {
    return this->tutorials.size();
}
/**
 * Copy constructor
 * @param _tutorials
 */
Tutorial Administrator::operator[](int index) {
    return this->tutorials[index];
}
/**
 * Copy constructor
 * @param _tutorials
 */
Tutorial Administrator::getElement(int position) {
    if(position<0 || position>=this->tutorials.size())
        throw MyExceptionAdministrator{"Invalid position!"};
    return this->tutorials[position];
}
/**
 * Copy constructor
 * @param _tutorials
 */
std::vector<Tutorial> Administrator::getAllTutorials() {
    return this->tutorials;
}