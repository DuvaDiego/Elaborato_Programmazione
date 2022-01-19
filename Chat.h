#ifndef ELABORATO_PROGRAMMAZIONE_CHAT_H
#define ELABORATO_PROGRAMMAZIONE_CHAT_H

#include <iostream>
#include <array>
#include "Message.h"
#include "SecondaryUser.h"

class Chat {
public:
    Chat(SecondaryUser* u, User* w);
    ~Chat();

    std::string getName() const;
    void setName(std::string newName);

    bool isBlocked() const;
    void setBlock(bool newSetup);

    void getChatMessages() const;
    void writeMessage(Message* newMessage);
    void setMessImportance(int n);

    SecondaryUser* getUser() const;
    void setUser(SecondaryUser* newUser);

    User* getWriter() const;
    void setWriter(User* newWriter);

private:
    std::string nameChat;
    bool blocked;
    std::list<Message*> messagesList;
    int maxSavedMessage = 10;
    SecondaryUser* user;
    User* writer;
};


#endif //ELABORATO_PROGRAMMAZIONE_CHAT_H
