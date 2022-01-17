#ifndef ELABORATO_PROGRAMMAZIONE_CHATREGISTER_H
#define ELABORATO_PROGRAMMAZIONE_CHATREGISTER_H

#include <iostream>
#include <list>
#include "Chat.h"

class ChatRegister {
public:
    explicit ChatRegister(std::list<Chat*> list, std::string o = "Diego");
    ~ChatRegister();

    bool getChatList() const;
    bool isEmpty() const;
    void addInChatList(Chat* newChat);
    Chat* removeChat(Chat* aChat);

    Chat* getCurrent() const;
    void setCurrent(Chat* newCurrent);

    std::string getOwner() const;

private:
    std::list<Chat*> chatList;
    Chat* currentChat;
    std::string owner;
};


#endif //ELABORATO_PROGRAMMAZIONE_CHATREGISTER_H
