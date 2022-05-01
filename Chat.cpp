#include "Chat.h"

Chat::Chat(std::shared_ptr<SecondaryUser> u, std::shared_ptr<User> w) : user(move(u)), writer(move(w)) {
    nameChat = user->getName();
    blocked = false;
}

Chat::~Chat() {
    for (auto& message : messagesList)
        message.reset();
    user.reset();
    writer.reset();
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

void Chat::writeMessage(std::shared_ptr<Message> &newMessage) {
    if (messagesList.size() == maxSavedMessage) {
        messagesList.pop_front();
    }
    messagesList.push_back(newMessage);

    newMessage->getText();
    std::cout << std::endl;
}

bool Chat::setMessImportance(unsigned int n) {
    if (n >= 0 && n < 10) {                                                                                             // caso settaggio importanza
        unsigned int quantity = messagesList.size();
        if (n > quantity - 1 && n < 10) {                                                                               // nel caso ci sono m < 10 messaggi nella chat, si può inserire
            std::cout << "\nNella Chat ci sono " << quantity << " messaggi." << std::endl;                              // un numero fino a m
            std::cout << "Il numero massimo che puoi inserire e' " << quantity << std::endl;
            return true;
        } else {                                                                                                        // caso generale settaggio importanza
            int i = 0;
            for (auto &message: messagesList) {                                                                         // scorre fino al messaggio desiderato
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
                    std::cout << std::endl;
                    return false;
                } else
                    i++;
            }
        }
    } else if (n == 10) {                                                                                               // caso per ottenere lista messaggi importanti
        getImportantMessages();
        return false;
    } else if (n == 11) {                                                                                                 // caso pulizia messaggi importanti
        if(!savedMessage.empty()) {
            savedMessage.clear();
            std::cout << "Lista messaggi importanti svuotata." << std::endl;
        }
        else
            std::cout << "Non ci sono messaggi importanti in questa Chat." << std::endl;
        std::cout << std::endl;
        return false;
    }

    std::cout << "Carattere non valido. " << std::endl;                                                                 // caso carattere non valido
    return true;
}

void Chat::getImportantMessages() const {
    if(savedMessage.empty()) {
        std::cout << "Non ci sono messaggi importanti in questa Chat." << std::endl;
    } else {
        for (auto &message: savedMessage) {
            std::cout << "\n- " << std::flush;
            message->getText();

            char ch = (char) 19;
            std::cout << "  " << ch << std::flush;
        }
    }
    std::cout << std::endl;
}

std::shared_ptr<SecondaryUser> Chat::getUser() const {
    return user;
}

void Chat::setUser(std::shared_ptr<SecondaryUser> newUser) {
    user = move(newUser);
}

std::shared_ptr<User> Chat::getWriter() const {
    return writer;
}

void Chat::setWriter(std::shared_ptr<User> newWriter) {
    writer = move(newWriter);
}