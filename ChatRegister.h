#ifndef ELABORATO_PROGRAMMAZIONE_CHATREGISTER_H
#define ELABORATO_PROGRAMMAZIONE_CHATREGISTER_H

#include <iostream>
#include <list>
#include "Chat.h"

class ChatRegister {
public:
    explicit ChatRegister(std::string o = "Diego");
    ~ChatRegister();

    void getChatList() const;
    bool isEmpty() const;
    void addInChatList(Chat* newChat);
    void removeChat(Chat* current);
    bool searchChat(std::string& nameChat);

    Chat* getCurrent() const;
    void setCurrent(Chat* newCurrent);

    std::string getOwner() const;

private:
    std::list<Chat*> chatList;
    Chat* currentChat;
    std::string owner;
};


#endif //ELABORATO_PROGRAMMAZIONE_CHATREGISTER_H
