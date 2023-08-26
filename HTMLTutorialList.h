//
// Created by DIANA on 5/6/2023.
//

#ifndef A45_DOROBAT_DIANA_HTMLTUTORIALLIST_H
#define A45_DOROBAT_DIANA_HTMLTUTORIALLIST_H
#include "FileTutorialList.h"

class HTMLTutorialList : public FileTutorialList {
public:

    void writeToFile() override;
    void displayTutorialList() const override;
};
#endif //A45_DOROBAT_DIANA_HTMLTUTORIALLIST_H
