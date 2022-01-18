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
    if (messagesList.empty()) {
        std::cout << "\nUltimi 10 messaggi della Chat:" << std::endl;
        for (auto &messages: messagesList) {
            std::cout << "\n- " << std::flush;
            messages->getText();
        }
    } else
        std::cout << "\nLa Chat e' vuota." << std::endl;
}

void Chat::writeMessage(Message *newMessage) {
    if (messagesList.size() == maxSavedMessage) {
        messagesList.pop_front();
    }
    messagesList.push_back(newMessage);

    newMessage->getText();
    std::cout << std::endl;
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