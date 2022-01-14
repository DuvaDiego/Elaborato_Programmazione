#include "Chat.h"

Chat::Chat(std::string name, std::list<Message *> list, SecondaryUser *u, bool b) : messagesList(move(list)), user(u), blocked(b) {
//FIXME: user dovrebbe essere una string, quindi sistemare l'iniziazione di name
    name = user->getName();
}

Chat::~Chat() {
    for (auto& message : messagesList)
        delete message;
}

std::string Chat::getName() const {
    return nameChat;
}

void Chat::setName(std::string newName) {
    nameChat = move(newName);
}

bool Chat::isBlocked() const {
    return blocked;
}

void Chat::setBlock(bool newSetup) {
    blocked = newSetup;
}

void Chat::getChatMessages() const {
    for (auto& messages : messagesList)
        std::cout << messages->getText() << std::endl;
}

SecondaryUser *Chat::getUser() const {
    return user;
}

void Chat::setUser(SecondaryUser *newUser) {
    user = newUser;
}

