#ifndef ELABORATO_PROGRAMMAZIONE_CHATREGISTER_H
#define ELABORATO_PROGRAMMAZIONE_CHATREGISTER_H

#include <iostream>
#include <list>
#include "Chat.h"

class ChatRegister {
public:
    explicit ChatRegister(std::list<Chat*> list, std::string o = "Diego");
    ~ChatRegister() = default;

    void getChatList();

    std::string getOwner();

private:
    std::list<Chat*> chatList;
    std::string owner;
};


#endif //ELABORATO_PROGRAMMAZIONE_CHATREGISTER_H
