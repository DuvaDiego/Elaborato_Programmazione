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
        ChatView::getMessages(messagesList, true);
    } else
        ChatView::getMessages(messagesList, false);
}

void Chat::writeMessage(std::shared_ptr<Message> &newMessage) {
    if (messagesList.size() == maxSavedMessage) {
        messagesList.pop_front();
    }
    messagesList.push_back(newMessage);
    ChatView::writeMessage(newMessage);
}

bool Chat::setMessImportance(unsigned int n) {
    unsigned int quantity = messagesList.size();
    if (!messagesList.empty()) {
        if (n >= 0 && n < 10) {                                                                                         // caso settaggio importanza
            if (n > quantity - 1) {                                                                                     // nel caso ci sono m < 10 messaggi nella chat, si può inserire un numero fino a m
                ChatView::sayImportance(0, quantity);
                return true;
            } else {
                int i = 0;
                for (auto &message: messagesList) {                                                                     // scorre fino al messaggio desiderato
                    if (i == n) {                                                                                       // caso settaggio importanza a true
                        if (message->getImportance()) {
                            message->setImportance(false);
                            ChatView::sayImportance(1, quantity);
                            savedMessage.remove(message);
                        } else {                                                                                        // caso settaggio importanza a false
                            message->setImportance(true);
                            ChatView::sayImportance(2, quantity);
                            savedMessage.push_back(message);
                        }
                        ChatView::writeMessage(message);
                        return false;
                    } else
                        i++;
                }
            }
        } else if (n == 10) {                                                                                           // caso lettura messaggi importanti
            if (savedMessage.empty()) {                                                                                 // caso lista messaggi importanti vuota
                ChatView::sayImportance(3, quantity);
                return false;
            } else {
                for (std::shared_ptr<Message> message: savedMessage)
                    ChatView::writeMessage(message);
                return false;
            }
        } else if (n == 11) {                                                                                           // caso pulizia messaggi importanti
            ChatView::sayImportance(4, quantity);
            return false;
        }
        ChatView::sayImportance(5,quantity);                                                                   // caso carattere non valido
        return true;
    } else {
        ChatView::sayImportance(6, quantity);                                                                  // caso chat vuota
        return false;
    }
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