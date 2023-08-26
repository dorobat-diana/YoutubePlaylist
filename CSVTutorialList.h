//
// Created by DIANA on 5/6/2023.
//

#ifndef A45_DOROBAT_DIANA_CSVTUTORIALLIST_H
#define A45_DOROBAT_DIANA_CSVTUTORIALLIST_H
//#include <windows.h>
#include "FileTutorialList.h"


class CSVTutorialList : public FileTutorialList {
public:

    void displayTutorialList() const override;
    void writeToFile() override;

};
#endif //A45_DOROBAT_DIANA_CSVTUTORIALLIST_H
