#include "ChatRegister.h"

ChatRegister::ChatRegister(std::list<Chat *> list, std::string o) : chatList(move(list)), owner(move(o)) {
}

ChatRegister::~ChatRegister() {
    for (auto& chat : chatList)
        delete chat;
}

bool ChatRegister::getChatList() const {
    if (isEmptyList()) {
        return false;
    }
    else {
        for (auto &chat: chatList)
            std::cout << chat->getName() << std::endl; //TODO: aggiungere la caratteristica delle chat preferite che compaiono in cima al registro
        return true;
    }
}

bool ChatRegister::isEmptyList() const {
    if (chatList.empty()) {
        std::cout << "\n Il registro al momento e' vuoto. Digitare:" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- Q| per ucire" << std::endl;
        return true;
    }
    return false;
}

void ChatRegister::addInChatList(Chat *newChat) {
    chatList.push_front(newChat);
    std::cout << "\nChat '" << newChat->getName() << "_' aggiunta al registro." << std::endl;
}

std::string ChatRegister::getOwner() const {
    return owner;
}