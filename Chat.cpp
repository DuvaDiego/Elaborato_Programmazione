#include "Chat.h"

Chat::Chat(std::shared_ptr<SecondaryUser> u, std::shared_ptr<User> w) : user(move(u)), writer(move(w)) {
    nameChat = user->getName();
    block = false;
    quantity = 0;
    quantityFound = 0;
    quantitySaved = 0;
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
    return block;
}

void Chat::setBlock(bool newSetup) {
    block = newSetup;
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

std::shared_ptr<Message> Chat::getSavedMessage(int number) const {
    auto it = savedMessage.begin();
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
    if (messagesList.size() == Max) {
        messagesList.pop_front();
        quantity--;
    }

    if (!messagesList.empty()) {
        messagesList.back()->setRead(true);                                                                     // Un messaggio viene letto quando l'altro utente risponde a tale messaggio.
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
    if (n >= 0 && n < Max) {                                                                                            // Caso eliminazione messaggio:
        if (n > quantityFound - 1) {                                                                                    // nel caso ci sono m < Max messaggi nella chat, si può inserire un numero fino a m;
            return true;
        } else {
            int i = 0;
            for (auto &message: messagesFound) {                                                                        // sennò scorre fino al messaggio desiderato ed
                if (i == n) {                                                                                           // elimina il messaggio scelto.
                    if(message->getImportance()) {
                        savedMessage.remove(message);                                                                   // Un messaggio eliminato non sta più tra i messaggi importanti.
                        quantitySaved--;
                        message->setImportance(false);
                    }

                    std::string cancelText = "Messaggio eliminato.";
                    std::list<std::string> text;
                    text.push_back(cancelText);
                    message->setText(text);

                    return false;
                } else
                    i++;
            }
        }
    } else if (n == Max + 2) {                                                                                          // Caso annulla operazione.
        return false;
    }
    return true;                                                                                                        // Caso carattere non valido.
}

bool Chat::setMessImportance(unsigned int n) {
    if (n >= 0 && n < Max) {                                                                                            // Caso settaggio importanza
        if (n > quantityFound - 1) {                                                                                    // nel caso ci sono m < Max messaggi nella chat, si può inserire un numero fino a m.
            return true;
        } else {
            int i = 0;
            for (auto &message: messagesFound) {                                                                        // Scorre fino al messaggio desiderato e
                if (i == n) {                                                                                           // imposta l'importanza a true
                    if (message->getImportance()) {
                        message->setImportance(false);
                        savedMessage.remove(message);
                        quantitySaved--;
                    } else {                                                                                            // o imposta l'importanza a false.
                        message->setImportance(true);
                        savedMessage.push_back(message);
                        quantitySaved++;
                    }
                    return false;
                } else
                    i++;
            }
        }
    } else if (n == Max || n == Max + 2) {                                                                              // Caso lettura messaggi importanti o annulla operazione
        return false;
    } else if (n == Max + 1) {                                                                                          // Caso pulizia messaggi importanti.
        for(auto& message : savedMessage)
            message->setImportance(false);

        savedMessage.erase(savedMessage.begin(), savedMessage.end());
        quantitySaved = 0;
        return false;
    }
    return true;                                                                                                        // Caso carattere non valido.
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

int Chat::getMessQuantity() const {
    return quantity;
}

int Chat::getFoundQuantity() const {
    return quantityFound;
}

int Chat::getSavedQuantity() const {
    return quantitySaved;
}