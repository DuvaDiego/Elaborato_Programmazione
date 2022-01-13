#include "PrimaryUser.h"

PrimaryUser::PrimaryUser(ChatRegister *reg, std::string name) : theRegister(reg), User(move(name)) {
}

void PrimaryUser::writeRegister() const {
    theRegister->getChatList();
}