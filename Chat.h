#ifndef ELABORATO_PROGRAMMAZIONE_CHAT_H
#define ELABORATO_PROGRAMMAZIONE_CHAT_H

#include <iostream>
#include <array>
#include "Message.h"
#include "SecondaryUser.h"

class Chat {
public:
    explicit Chat(SecondaryUser* u, bool b = false);
    ~Chat();

    std::string getName() const;
    void setName(std::string newName);

    bool isBlocked() const;
    void setBlock(bool newSetup);

    void getChatMessages() const;

    SecondaryUser* getUser() const;
    void setUser(SecondaryUser* newUser);

    User* getWriter() const;
    void setWriter(User* newWriter);

private:
    std::string nameChat;
    bool blocked;
    std::array<Message*, 10> messagesList; //TODO: aggiungere i nuovi messaggi in testa alla lista
    SecondaryUser* user;
    User* writer;
};


#endif //ELABORATO_PROGRAMMAZIONE_CHAT_H
