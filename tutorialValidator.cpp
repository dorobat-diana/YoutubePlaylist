//
// Created by DIANA on 5/5/2023.
//

#include "tutorialValidator.h"
#include "tutorial.h"

ValidationException::ValidationException(std::string _message) : message{_message} {}

std::string ValidationException::getMessage() const {
    return this->message;
}

ValidationExceptionInherited::ValidationExceptionInherited(std::string _message) : message{_message} {}

const char *ValidationExceptionInherited::what() const noexcept {
    return message.c_str();
}

void ValidatorTutorial::validate( Tutorial t) {
    std::string errors;
    if (t.getTitle().size() < 3)
        errors += std::string("The tutorial title cannot be less than 2 characters!\n");
    if (t.getPresenter().size() < 3)
        errors += std::string("The presenter's name cannot be less than 2 characters!\n");
    if (t.getDurationMinutes() < 1)
        errors += std::string("The duration cannot be less than 1 minute!\n");
    if (t.getDurationSeconds() < 0)
        errors += std::string("The duration cannot be less than 0 seconds!\n");
    if (t.getLikes() < 0)
        errors += std::string("The number of likes cannot be less than 0!\n");
    if (t.getLink().find("www") != 0)
        errors += std::string("The link must start with www!\n");

    if (errors.size() > 0)
        throw ValidationException(errors);
}