//
// Created by DIANA on 5/6/2023.
//

#ifndef A45_DOROBAT_DIANA_FILETUTORIALLIST_H
#define A45_DOROBAT_DIANA_FILETUTORIALLIST_H
#include "administrator.h"
class FileTutorialList :
public Administrator
{
    protected:
        std::string filename;
    public:
        FileTutorialList();
        virtual ~FileTutorialList() {}

        void setFilename(const std::string& filename);
        virtual void writeToFile() = 0;
        virtual void displayTutorialList() const = 0;
        std::string getFilename() const;
};
#endif //A45_DOROBAT_DIANA_FILETUTORIALLIST_H
