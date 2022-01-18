#include "Chat.h"

Chat::Chat(SecondaryUser *u, bool b) : user(u), blocked(b) {
    nameChat = user->getName();
    writer = user;
}

Chat::~Chat() {
    for (auto& message : messagesList)
        delete message;
    delete user;
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
    for (auto& messages : messagesList) {
        messages->getText();
    }
}

SecondaryUser *Chat::getUser() const {
    return user;
}

void Chat::setUser(SecondaryUser *newUser) {
    user = newUser;
}

User *Chat::getWriter() const {
    return writer;
}

void Chat::setWriter(User *newWriter) {
    writer = newWriter;
}