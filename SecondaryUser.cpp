#include "SecondaryUser.h"

SecondaryUser::SecondaryUser(bool f, std::string name) : favourite(f), User(move(name)) {
}

bool SecondaryUser::isFavourite() const {
    return favourite;
}

void SecondaryUser::setFavouritism(bool favouritism) {
    favourite = favouritism;
}