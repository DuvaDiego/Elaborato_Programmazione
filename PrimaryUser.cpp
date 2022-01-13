#include "PrimaryUser.h"

PrimaryUser::PrimaryUser(ChatRegister *reg, std::string name) : theRegister(reg), User(move(name)) {
}

PrimaryUser::~PrimaryUser() {
    if (theRegister != nullptr)
        delete theRegister;
}

void PrimaryUser::writeRegister() const {
    theRegister->getChatList();
}