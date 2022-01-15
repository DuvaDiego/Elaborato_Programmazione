#include "ChatRegister.h"

ChatRegister::ChatRegister(std::list<Chat *> list, std::string o) : chatList(move(list)), owner(move(o)) {
}

ChatRegister::~ChatRegister() {
    for (auto& chat : chatList)
        delete chat;
}

bool ChatRegister::getChatList() const {
    if (chatList.empty()) {
        std::cout << "\n Il registro al momento e' vuoto. Digitare - C| per creare una chat." << std::endl;
        return false;
    }
    else {
        for (auto &chat: chatList)
            std::cout << chat->getName() << std::endl; //TODO: aggiungere la caratteristica delle chat preferite che compaiono in cima al registro
        return true;
    }
}

std::string ChatRegister::getOwner() const {
    return owner;
}