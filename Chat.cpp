#include "Chat.h"

Chat::Chat(std::shared_ptr<SecondaryUser> u, std::shared_ptr<User> w) : user(move(u)), writer(move(w)) {
    nameChat = user->getName();
    blocked = false;
}

Chat::~Chat() {
    for (auto& message : messagesList)
        message.reset();
    for (auto& message : savedMessage)
        message.reset();
    for (auto& message : messagesFound)
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

    if (!messagesList.empty()) {
        messagesList.back()->setRead(true);                                                                     // un messaggio viene letto quando l'altro utente risponde a tale messaggio
    }

    messagesList.push_back(newMessage);

    ChatView::writeMessage(newMessage);
}

void Chat::searchMessages(std::string &word) {
    if (!messagesList.empty()) {
        int corresponding = 0;

        messagesFound.erase(messagesFound.begin(), messagesFound.end());
        for (auto &message: messagesList) {
            if (message->searchWord(word)) {
                messagesFound.push_back(message);
                corresponding++;
            }
        }
        ChatView::correspondingMessage(corresponding, messagesFound);
    } else
        ChatView::getMessages(messagesList, false);
}

bool Chat::setMessImportance(unsigned int n) { //FIXME: per l'importanza e la cancellazione usare la ricerca del messaggio
    unsigned int quantity = messagesFound.size();
    if (!messagesList.empty()) {
        if (n >= 0 && n < Max) {                                                                                        // caso settaggio importanza
            if (n > quantity - 1) {                                                                                     // nel caso ci sono m < 10 messaggi nella chat, si può inserire un numero fino a m
                ChatView::sayImportance(0, quantity);
                return true;
            } else {
                int i = 0;
                for (auto &message: messagesFound) {                                                                    // scorre fino al messaggio desiderato
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
        } else if (n == Max) {                                                                                          // caso lettura messaggi importanti
            if (savedMessage.empty()) {                                                                                 // caso lista messaggi importanti vuota
                ChatView::sayImportance(3, quantity);
                return false;
            } else {
                for (std::shared_ptr<Message> message: savedMessage)
                    ChatView::writeMessage(message);
                return false;
            }
        } else if (n == Max + 1) {                                                                                      // caso pulizia messaggi importanti
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