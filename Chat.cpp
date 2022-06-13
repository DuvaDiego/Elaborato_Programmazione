#include "Chat.h"

Chat::Chat(std::shared_ptr<SecondaryUser> u, std::shared_ptr<User> w) : user(move(u)), writer(move(w)) {
    nameChat = user->getName();
    blocked = false;
    quantity = 0;
    quantityFound = 0;
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

std::shared_ptr<Message> Chat::getMessage(int number) const {
    auto it = messagesList.begin();
    int i = 0;
    while (i < number) {
        it++;
        i++;
    }
    return it.operator*();
}

std::shared_ptr<Message> Chat::getFoundMessage(int number) const {
    auto it = messagesFound.begin();
    int i = 0;
    while (i < number) {
        it++;
        i++;
    }
    return it.operator*();
}

void Chat::writeMessage(std::shared_ptr<Message> &newMessage) {
    if (messagesList.size() == maxSavedMessage) {
        messagesList.pop_front();
        quantity--;
    }

    if (!messagesList.empty()) {
        messagesList.back()->setRead(true);                                                                     // un messaggio viene letto quando l'altro utente risponde a tale messaggio
    }

    messagesList.push_back(newMessage);
    quantity++;
}

bool Chat::searchMessages(std::string &word) {
    if (!messagesList.empty()) {

        messagesFound.erase(messagesFound.begin(), messagesFound.end());
        quantityFound = 0;
        for (auto &message: messagesList) {
            if (message->searchWord(word)) {
                messagesFound.push_back(message);
                quantityFound++;
            }
        }
        if (quantityFound != 0)
            return true;
    }
    return false;
}

bool Chat::cancelMessage(unsigned int n) {
    /*unsigned int quantity = messagesFound.size();
    if (n >= 0 && n < Max) {                                                                                            // caso eliminazione messaggio
        if (n > quantity - 1) {                                                                                         // nel caso ci sono m < Max messaggi nella chat, si può inserire un numero fino a m
            ChatView::selectionCase(0, quantity);
            return true;
        } else {
            int i = 0;
            for (auto &message: messagesFound) {                                                                        // scorre fino al messaggio desiderato
                if (i == n) {                                                                                           // elimina il messaggio scelto
                    std::string cancelText = "Messaggio eliminato.";
                    std::list<std::string> text;
                    text.push_back(cancelText);
                    message->setText(text);

                    ChatView::selectionCase(1, quantity);
                    return false;
                } else
                    i++;
            }
        }
    } else if (n == Max + 2) {                                                                                          // caso annulla operazione
        ChatView::selectionCase(6, quantity);
        return false;
    }
    ChatView::selectionCase(7, quantity);                                                                      // caso carattere non valido
    return true;*/
    return false;
}

bool Chat::setMessImportance(unsigned int n) {
    /*unsigned int quantity = messagesFound.size();
    if (n >= 0 && n < Max) {                                                                                            // caso settaggio importanza
        if (n > quantity - 1) {                                                                                         // nel caso ci sono m < Max messaggi nella chat, si può inserire un numero fino a m
            ChatView::selectionCase(0, quantity);
            return true;
        } else {
            int i = 0;
            for (auto &message: messagesFound) {                                                                        // scorre fino al messaggio desiderato
                if (i == n) {                                                                                           // caso settaggio importanza a true
                    if (message->getImportance()) {
                        message->setImportance(false);
                        ChatView::selectionCase(2, quantity);
                        savedMessage.remove(message);
                    } else {                                                                                            // caso settaggio importanza a false
                        message->setImportance(true);
                        ChatView::selectionCase(3, quantity);
                        savedMessage.push_back(message);
                    }
                    ChatView::writeMessage(message);
                    return false;
                } else
                    i++;
            }
        }
    } else if (n == Max) {                                                                                              // caso lettura messaggi importanti
        if (savedMessage.empty()) {                                                                                     // caso lista messaggi importanti vuota
            ChatView::selectionCase(4, quantity);
            return false;
        } else {
            for (std::shared_ptr<Message> message: savedMessage)
                ChatView::writeMessage(message);
            return false;
        }
    } else if (n == Max + 1) {                                                                                          // caso pulizia messaggi importanti
        ChatView::selectionCase(5, quantity);
        return false;
    } else if (n == Max + 2) {
        ChatView::selectionCase(6, quantity);                                                                  // caso annulla operazione
        return false;
    }
    ChatView::selectionCase(7, quantity);                                                                      // caso carattere non valido
    return true;*/
    return false;
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

int Chat::getMessageQuantity() const {
    return quantity;
}

int Chat::getFoundQuantity() const {
    return quantityFound;
}