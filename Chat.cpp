#include "Chat.h"

Chat::Chat(SecondaryUser *u, User* w) : user(u), writer(w) {
    nameChat = user->getName();
    blocked = false;
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
    if (!messagesList.empty()) {
        std::cout << "\nUltimi 10 messaggi della Chat:" << std::endl;
        for (auto &messages: messagesList) {
            std::cout << "\n- " << std::flush;
            messages->getText();
        }
        std::cout << std::endl;
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

void Chat::setMessImportance(int n) {
    for (auto& message : messagesList) {
        int i = 0;
        if (i == n) {
            if (message->getImportance()) {
                message->setImportance(false);
                std::cout << "Il messaggio '" << std::flush;
                message->getText();
                std::cout << "' non e' più importante." << std::endl;
            } else {
                message->setImportance(true);
                std::cout << "Il messaggio '" << std::flush;
                message->getText();
                std::cout << "' e' ora importante." << std::endl;
            }
            break;
        } else
            i++;
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