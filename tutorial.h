//
// Created by DIANA on 3/31/2023.
//

#ifndef A45_DOROBAT_DIANA_TUTORIAL_H
#define A45_DOROBAT_DIANA_TUTORIAL_H
#include <iostream>
using namespace std;
class Tutorial {
private:
    string title;
    string presenter;
    int duration_minutes;
    int duration_seconds;
    int likes;
    string link;
public:
    //default constructor
    Tutorial()=default;
    //constructor
    Tutorial(string title, string presenter, int duration_minutes, int duration_seconds, int likes, string link);
    //destructor
    ~Tutorial();
    //returns the title of the tutorial
    string getTitle();
    //returns the presenter of the tutorial
    string getPresenter();
    //returns the duration of the tutorial
    int getDurationMinutes();
    //returns the duration of the tutorial
    int getDurationSeconds();
    //returns the number of likes of the tutorial
    int getLikes();
    //returns the link of the tutorial
    string getLink();
    //sets the title of the tutorial
    void setTitle(string title);
    //sets the presenter of the tutorial
    void setPresenter(string presenter);
    //sets the duration of the tutorial
    void setDurationMinutes(int duration_minutes);
    //sets the duration of the tutorial
    void setDurationSeconds(int duration_seconds);
    //sets the number of likes of the tutorial
    void setLikes(int likes);
    //sets the link of the tutorial
    void setLink(string link);

    bool operator==(Tutorial a);

    friend std::istream& operator>>(std::istream& it, Tutorial& t);

    friend std::ostream& operator<<(std::ostream& ot, const Tutorial& t);



};
#endif //A45_DOROBAT_DIANA_TUTORIAL_H
