#ifndef ELABORATO_PROGRAMMAZIONE_CHAT_H
#define ELABORATO_PROGRAMMAZIONE_CHAT_H

#include <iostream>
#include <list>
#include "Message.h"
#include "SecondaryUser.h"

class Chat {
public:
    Chat(std::string name, std::list<Message*> list, SecondaryUser* u, bool b = false);
    ~Chat() = default;

    std::string getName() const;
    void setName(std::string newName);

    bool isBlocked() const;
    void setBlock(bool newSetup);

    void getChatMessages() const;

    //FIXME: vanno sistemti i metodi getter e setter dell'utente secondario (anche le definizioni)
    SecondaryUser* getUser() const;
    void setUser(SecondaryUser* newUser);

private:
    std::string nameChat;
    bool blocked;
    std::list<Message*> messagesList; //TODO aggiungere i nuovi messaggi in testa alla lista
    SecondaryUser* user;
};


#endif //ELABORATO_PROGRAMMAZIONE_CHAT_H
