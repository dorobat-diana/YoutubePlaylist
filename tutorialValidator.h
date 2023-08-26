//
// Created by DIANA on 5/5/2023.
//

#ifndef A45_DOROBAT_DIANA_TUTORIALVALIDATOR_H
#define A45_DOROBAT_DIANA_TUTORIALVALIDATOR_H

#include <string>
#include "tutorial.h"

class ValidationException{
private:
    std::string message;
public:
    ValidationException(std::string _message);
    std::string getMessage() const;
};

class ValidationExceptionInherited : public std::exception
{
private:
    std::string message;
public:
    ValidationExceptionInherited(std::string _message);
    const char* what() const noexcept override;
};

class ValidatorTutorial {
public:
    static void validate(Tutorial t);
};
#endif //A45_DOROBAT_DIANA_TUTORIALVALIDATOR_H
