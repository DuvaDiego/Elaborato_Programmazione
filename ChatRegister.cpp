#include "ChatRegister.h"

ChatRegister::ChatRegister(std::list<Chat *> list, std::string o) : chatList(move(list)), owner(move(o)) {
}

ChatRegister::~ChatRegister() {
    for (auto& chat : chatList)
        delete chat;
}

void ChatRegister::getChatList() const {
    for (auto& chat : chatList)
        std::cout << chat->getName() << std::endl; //TODO aggiungere la caratteristica delle chat preferite che compaiono in cima al registro
}

std::string ChatRegister::getOwner() const {
    return owner;
}