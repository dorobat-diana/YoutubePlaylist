//
// Created by DIANA on 3/31/2023.
//

#include "tutorial.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
/**
 * Default constructor
 */
Tutorial::Tutorial(string title, string presenter, int duration_minutes, int duration_seconds, int likes, string link)
        : title{title}, presenter{presenter},
          duration_minutes{duration_minutes},
          duration_seconds{duration_seconds}, likes{likes}, link{link} {}

/**
 * destroy the object
 */
Tutorial::~Tutorial() {

}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
string Tutorial::getTitle() {
    return this->title;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
string Tutorial::getPresenter() {
    return this->presenter;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
int Tutorial::getDurationMinutes() {
    return this->duration_minutes;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
int Tutorial::getDurationSeconds() {
    return this->duration_seconds;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
int Tutorial::getLikes() {
    return this->likes;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
string Tutorial::getLink() {
    return this->link;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
void Tutorial::setTitle(string title) {
    this->title = title;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
void Tutorial::setPresenter(string presenter) {
    this->presenter = presenter;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
void Tutorial::setDurationMinutes(int duration_minutes) {
    this->duration_minutes = duration_minutes;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
void Tutorial::setDurationSeconds(int duration_seconds) {
    this->duration_seconds = duration_seconds;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
void Tutorial::setLikes(int likes) {
    this->likes = likes;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
void Tutorial::setLink(string link) {
    this->link = link;
}
/**
 * Copy constructor
 * @param tutorial
 * @return
 */
bool Tutorial::operator==(const Tutorial a) {
    if(a.duration_minutes != this->duration_minutes){
        return false;
    }
    if(a.duration_seconds != this->duration_seconds){
        return false;
    }
    if(a.likes != this->likes){
        return false;
    }
    if(a.link != this->link){
        return false;
    }
    if(a.presenter != this->presenter){
        return false;
    }
    if(a.title != this->title){
        return false;
    }

    return true;
}


vector<string> tokensize(string str, char delimiter){
    vector<string> result;
    stringstream ss(str);
    string token;
    while(getline(ss, token, delimiter)){
        result.push_back(token);
    }
    return result;
}


std::istream& operator>>(std::istream& it, Tutorial& t){
    string line;
    getline(it, line);
    vector<string> tokens = tokensize(line, ',');
    if(tokens.size() != 6){
        return it;
    }
    t.title = tokens[0];
    t.presenter = tokens[1];
    t.duration_minutes = stoi(tokens[2]);
    t.duration_seconds = stoi(tokens[3]);
    t.likes = stoi(tokens[4]);
    t.link = tokens[5];
    return it;
}

std::ostream& operator<<(std::ostream& ot, const Tutorial& t){
    ot << t.title << "," << t.presenter << "," << t.duration_minutes << "," << t.duration_seconds << "," << t.likes << "," << t.link << "\n";
    return ot;
}
