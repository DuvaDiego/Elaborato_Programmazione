#include "PrimaryUser.h"

PrimaryUser::PrimaryUser(std::shared_ptr<Register> reg, std::string name) : theRegister(move(reg)), User(move(name)) {
}

PrimaryUser::~PrimaryUser() {
    theRegister.reset();
}