#include "SecondaryUser.h"

SecondaryUser::SecondaryUser(std::string name, bool f) : User(move(name)), favourite(f) {
}

bool SecondaryUser::isFavourite() const {
    return favourite;
}

void SecondaryUser::setFavouritism(bool favouritism) {
    favourite = favouritism;
}