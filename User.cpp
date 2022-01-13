#include "User.h"

User::User(std::string name) : nickName(move(name)) {
}

std::string User::getName() const {
    return nickName;
}

void User::setName(std::string newNickName) {
    nickName = move(newNickName);
}