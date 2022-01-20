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
        std::cout << "\nUltimi 10 messaggi della Chat:" << std::flush;
        for (auto &messages: messagesList) {
            std::cout << "\n- " << std::flush;
            messages->getText();

            if (messages->getImportance()) {
                char ch = (char) 19;
                std::cout << "  " << ch << std::flush;
            }
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

void Chat::setMessImportance(unsigned int n) {
    unsigned int quantity = messagesList.size();
    if (n > quantity - 1 && n <= 9) {
        std::cout << "\nNella Chat ci sono " << quantity << " messaggi." << std::endl;
        std::cout << "Il numero massimo che puoi inerire e' " << quantity - 1 << std::endl;
    } else {
        int i = 0;
        for (auto &message: messagesList) {
            if (i == n) {
                if (message->getImportance()) {
                    message->setImportance(false);
                    std::cout << "Messaggio non piu' importante -" << std::flush;
                    message->getText();

                    savedMessage.remove(message);
                } else {
                    message->setImportance(true);
                    std::cout << "Messaggio importante -" << std::flush;
                    message->getText();

                    savedMessage.push_back(message);
                }
                std::cout << std::endl;
                break;
            } else
                i++;
        }
    }
}

void Chat::getImportantMessages() const {
    if(savedMessage.empty()) {
        std::cout << "\nNon ci sono messaggi importanti in questa Chat." << std::endl;
    } else {
        for (auto &message: savedMessage) {
            std::cout << "\n- " << std::flush;
            message->getText();

            char ch = (char) 19;
            std::cout << "  " << ch << std::flush;
        }
        std::cout << std::endl;
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