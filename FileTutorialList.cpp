//
// Created by DIANA on 5/6/2023.
//

#include "FileTutorialList.h"

FileTutorialList::FileTutorialList() : Administrator{}, filename{""} {}

void FileTutorialList::setFilename(const std::string& filename) {
    this->filename = filename;
}

std::string FileTutorialList::getFilename() const {
    return this->filename;
}